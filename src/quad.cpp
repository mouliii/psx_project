#include "quad.h"

QuadBase::QuadBase(int32_t posx, int32_t posy, int16_t width, int16_t height)
   :
        localVerts(4), worldVerts(4),
        pos{posx,posy}
{
    int32_t centerX = width >> 1;
    int32_t centerY = height >> 1;
    localVerts.PushBack({-centerX, -centerY});
    localVerts.PushBack({+centerX, -centerY});
    localVerts.PushBack({-centerX, +centerY});
    localVerts.PushBack({+centerX, +centerY});
    Update();
    // 0---1
    // | / |
    // 2---3
} 

void QuadBase::Scale(CKSDK::Fixed::Fixed<int32_t, 12> scale)
{
    this->scale *= scale;
    update = true;
}
void QuadBase::Rotate(int16_t deg)
{// TODO optimization??
    angle += deg * ONE / 360;
    update = true;
}

void QuadBase::Translate(int32_t posx, int32_t posy)
{
    pos[0] += posx;
    pos[1] += posy;
    update = true;
}

void QuadBase::Update()
{// Scale-Rotate-Translate
    int32_t cachedCos = ccos(angle);
    int32_t cachedSin = csin(angle);
    int32_t cscale = scale.Raw();
    for (size_t i = 0; i < localVerts.Length(); i++)
    {
        int32_t scaledx = (localVerts[i].x * cscale) >> 12;
        int32_t scaledy = (localVerts[i].y * cscale) >> 12;

        worldVerts[i].x = ((scaledx * cachedCos) - (scaledy * cachedSin)) >> 12;
        worldVerts[i].y = ((scaledx * cachedSin) + (scaledy * cachedCos)) >> 12;

        worldVerts[i].x += pos[0].Raw() >> 12;
        worldVerts[i].y += pos[1].Raw() >> 12;
    }
}

QuadF::QuadF(int32_t posx, int32_t posy, int16_t width, int16_t height, Color color)
    :
    QuadBase(posx,posy,width,height),
    color(color)
{
}

void QuadF::Draw(Graphics &gfx, int z)
{
    if (update){
        Update();
        update = false;
    }
    POLY_F4* quad = gfx.NewPrimitive<POLY_F4>(z);
    setPolyF4(quad);
    setRGB0(quad, color.r,color.g,color.b);
    setXY4(quad, worldVerts[0].x, worldVerts[0].y, worldVerts[1].x, worldVerts[1].y, worldVerts[2].x, worldVerts[2].y, worldVerts[3].x, worldVerts[3].y);
}

void QuadF::SetColor(uint8_t r, uint8_t g, uint8_t b)
{
    color.SetColor(r,g,b);
}

QuadFT::QuadFT(int32_t posx, int32_t posy, int16_t width, int16_t height, Texture *tex, Color brightness)
    :
    QuadBase(posx,posy,width,height),
    texture(tex),
    uv(4),
    brightness(brightness)
{
    for (size_t i = 0; i < uv.Length(); i++)
    {
        uv.PushBack({.x = tex->UVoffs[0], .y=tex->UVoffs[1]});
    }
    
    //uv[0].x = 0;
    //uv[0].y = 0;
    uv[1].x += width;
    //uv[1].y = 0;
    //uv[2].x = 0;
    uv[2].y += height;
    uv[3].x += width;
    uv[3].y += height;
}

void QuadFT::Draw(Graphics &gfx, int z)
{
    if (update){
        Update();
        update = false;
    }
    POLY_FT4* quad = gfx.NewPrimitive<POLY_FT4>(z);
    setPolyFT4(quad);
    setRGB0(quad,brightness.r,brightness.g,brightness.b);
    setXY4(quad, worldVerts[0].x, worldVerts[0].y, worldVerts[1].x, worldVerts[1].y, worldVerts[2].x, worldVerts[2].y, worldVerts[3].x, worldVerts[3].y);
    setUV4(quad, uv[0].x, uv[0].y, uv[1].x, uv[1].y, uv[2].x, uv[2].y, uv[3].x, uv[3].y);
    setClut(quad, texture->clutCoords[0], texture->clutCoords[1]);//TODO (if <16 bit)
    setTPage( quad, texture->mode&0x3, 0, texture->texCoords[0], texture->texCoords[1] );
}

void QuadFT::SetUV(uint8_t vertIndex, uint16_t x, uint16_t y)
{
    uv[vertIndex].x = texture->UVoffs[0] + x;
    uv[vertIndex].y = texture->UVoffs[1] + y;
}

void QuadFT::SetBrightness(uint8_t b)
{
    brightness.SetColor(b,b,b);
}

QuadG::QuadG(int32_t posx, int32_t posy, int16_t width, int16_t height)
    :
    QuadBase(posx,posy,width,height),
    vertColor(4)
{
    for (size_t i = 0; i < vertColor.Length(); i++)
    {// ei toimi????
        vertColor.PushBack(Color(128,128,128));
    }
}

void QuadG::Draw(Graphics &gfx, int z)
{
    if (update){
        Update();
        update = false;
    }
    POLY_G4* quad = gfx.NewPrimitive<POLY_G4>(z);
    setPolyG4(quad);
    setRGB0(quad,vertColor[0].r,vertColor[0].g,vertColor[0].b);
    setRGB1(quad,vertColor[1].r,vertColor[1].g,vertColor[1].b);
    setRGB2(quad,vertColor[2].r,vertColor[2].g,vertColor[2].b);
    setRGB3(quad,vertColor[3].r,vertColor[3].g,vertColor[3].b);
    setXY4(quad, worldVerts[0].x, worldVerts[0].y, worldVerts[1].x, worldVerts[1].y, worldVerts[2].x, worldVerts[2].y, worldVerts[3].x, worldVerts[3].y);
    
}

void QuadG::SetColor(uint8_t vertIndex, Color color)
{
    vertColor[vertIndex] = color;
}

QuadGT::QuadGT(int32_t posx, int32_t posy, int16_t width, int16_t height, Texture *tex)
    :
    QuadBase(posx,posy,width,height),
    texture(tex),
    uv(4),
    vertColor(4)
{
    for (size_t i = 0; i < uv.Length(); i++)
    {
        uv.PushBack({.x = tex->UVoffs[0], .y=tex->UVoffs[1]});
    }
    uv[1].x += width;
    uv[2].y += height;
    uv[3].x += width;
    uv[3].y += height;
    for (size_t i = 0; i < vertColor.Length(); i++)
    {// ei toimi????
        vertColor.PushBack(Color(128,128,128));
    }
}

void QuadGT::Draw(Graphics &gfx, int z)
{
    POLY_GT4* quad = gfx.NewPrimitive<POLY_GT4>(z);
    setPolyGT4(quad);
    setRGB0(quad,vertColor[0].r,vertColor[0].g,vertColor[0].b);
    setRGB1(quad,vertColor[1].r,vertColor[1].g,vertColor[1].b);
    setRGB2(quad,vertColor[2].r,vertColor[2].g,vertColor[2].b);
    setRGB3(quad,vertColor[3].r,vertColor[3].g,vertColor[3].b);
    setXY4(quad, worldVerts[0].x, worldVerts[0].y, worldVerts[1].x, worldVerts[1].y, worldVerts[2].x, worldVerts[2].y, worldVerts[3].x, worldVerts[3].y);
    setUV4(quad, uv[0].x, uv[0].y, uv[1].x, uv[1].y, uv[2].x, uv[2].y, uv[3].x, uv[3].y);
    setClut(quad, texture->clutCoords[0], texture->clutCoords[1]);//TODO (if <16 bit)
    setTPage( quad, texture->mode&0x3, 0, texture->texCoords[0], texture->texCoords[1] );
}

void QuadGT::SetUV(uint8_t vertIndex, uint16_t x, uint16_t y)
{
    uv[vertIndex].x = texture->UVoffs[0] + x;
    uv[vertIndex].y = texture->UVoffs[1] + y;
}

void QuadGT::SetColor(uint8_t vertIndex, Color color)
{
    vertColor[vertIndex] = color;
}
