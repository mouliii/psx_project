#include "texture.h"

Texture::Texture()
{
}

//void Texture::UploadTexture(std::uint32_t *tim)
//{
//    TIM_IMAGE timImg;
//    GetTimInfo(tim, &timImg);
//    // upload pixel data
//    LoadImage(timImg.prect, timImg.paddr);
//    DrawSync(0); // recommended to wait for upload to complete
//    if (timImg.mode & 0x8) // bit 4
//    {   // if clut exist
//        LoadImage(timImg.crect, timImg.caddr);
//        DrawSync(0);
//        // vram clut coords
//        clutCoords[0] = timImg.crect->x;
//        clutCoords[1] = timImg.crect->y;
//    }
//    // vram tex coords
//    texCoords[0] = timImg.prect->x;
//    texCoords[1] = timImg.prect->y;
//    // vram page aligment UV offset                            v bit depth (0:4; 1:8; 2:16)
//    UVoffs[0] = (timImg.prect->x % 64) << (2 - (timImg.mode & 0x3));
//    UVoffs[1] = (timImg.prect->y & 0xff);
//
//    tPage = getTPage(timImg.mode & 0x3, 0, timImg.prect->x, timImg.prect->y);
//}