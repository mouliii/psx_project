#pragma once
#include <cstdint>
#include <psxgpu.h>

// ällö väri default load failure
// load ram -> upload vram -> delete ram

class Texture
{
public:
    Texture();
    // moved to graphics class
    //void UploadTexture(std::uint32_t* tim);
public:
    std::uint16_t UVoffs[2]; // tpage_offset + vec2(u,v)
    std::uint16_t clutCoords[2];
    std::uint16_t texCoords[2]; // x,y in vram
    std::uint16_t tPage;
    std::uint32_t mode;
};

//just store the value returned by getTPage()
//and pass it to setDrawTPage() through a variable