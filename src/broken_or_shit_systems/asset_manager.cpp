#include "asset_manager.h"
#include <cstring>

AssetManager::AssetManager(CdDrive &cd, Graphics &gfx)
    :
    cd(cd),gfx(gfx)
{
}

Ref<Texture> *AssetManager::LoadTexture(const char *name)
{
    for (std::uint32_t i = 0; i < nAssets; i++)
    {   // match
        if (std::strncmp(name, textures[i].name, 8) == 0 )
        {
            textures[i].refCount++;
            return &textures[i];
        }
    }
    // not cached load it
    auto* data = cd.LoadFile(name);
    Texture* tex = new Texture();
    // upload to vram and save texture data(pos,uv_offs, ...)
    gfx.UploadTexture(data, tex);
    // create Reference, set data pointer and copy it to array
    Ref<Texture> refTex(tex);
    textures[nextTexSpot] = refTex;
    if (++nextTexSpot > (nAssets - 1))
    {
        // TODO
        assert(nextTexSpot <= nAssets);
    }
    return &textures[nextTexSpot-1];
}