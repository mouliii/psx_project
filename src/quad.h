#pragma once
#include <psxgte.h>
#include "graphics.h"
#include "fixed_math.h"
#include "smart_arr.h"
#include "color.h"
#include "debug_msg.h"

struct Vertex2D
{
    int32_t x;
    int32_t y;
};

struct UV
{
    uint16_t x;
    uint16_t y;
};

// QUADS DO NOT FREE TEXTURES

//TODO Set_X
class QuadBase
{
public:
    QuadBase() = default;
    QuadBase(int32_t posx, int32_t posy, int16_t width, int16_t height);
    virtual ~QuadBase() = default;
    virtual void Draw(Graphics& gfx, int z) = 0;
    void Scale(CKSDK::Fixed::Fixed<int32_t, 12> scale);
    void Rotate(int16_t deg);
    void Translate(int32_t posx, int32_t posy);
    void Update();
public:
    CKSDK::Fixed::Fixed<int32_t, 12>pos[2];
    CKSDK::Fixed::Fixed<int32_t, 12> angle = 1; // _fixed; 4096 equals to 360 degrees | 1.0 scale
    CKSDK::Fixed::Fixed<int32_t, 12> scale = 1;
    bool update = false;
    Mou::SmartArr<Vertex2D> localVerts;
    Mou::SmartArr<Vertex2D> worldVerts;
};

class QuadF : public QuadBase
{
public:
    QuadF(int32_t posx, int32_t posy, int16_t width, int16_t height, Color color);
    virtual ~QuadF() = default;
    virtual void Draw(Graphics& gfx, int z) override;
    void SetColor(uint8_t r, uint8_t g, uint8_t b);
public:
    Color color;
};

class QuadFT : public QuadBase
{
public:
    QuadFT(int32_t posx, int32_t posy, int16_t width, int16_t height, Texture* tex, Color brightness={128,128,128});
    ~QuadFT() = default;
    virtual void Draw(Graphics& gfx, int z) override;
    void SetBrightness();//_fixed in
    void SetUV(uint8_t vertIndex, uint16_t x, uint16_t y);
    void SetBrightness(uint8_t b);
    // flip hor/vert (uv)
public:
    Texture* texture;
    Mou::SmartArr<UV> uv;
    Color brightness;
};

class QuadG : public QuadBase
{
public:
    QuadG(int32_t posx, int32_t posy, int16_t width, int16_t height);
    ~QuadG() = default;
    virtual void Draw(Graphics& gfx, int z) override;
    void SetColor(uint8_t vertIndex, Color color);
public:
    Mou::SmartArr<Color> vertColor;
};

class QuadGT : public QuadBase
{
public:
    QuadGT(int32_t posx, int32_t posy, int16_t width, int16_t height, Texture* tex);
    ~QuadGT(){}
    virtual void Draw(Graphics& gfx, int z) override;
    void SetUV(uint8_t vertIndex, uint16_t x, uint16_t y);
    void SetColor(uint8_t vertIndex, Color color);
public:
    Texture* texture;
    Mou::SmartArr<UV> uv;
    Mou::SmartArr<Color> vertColor;
};