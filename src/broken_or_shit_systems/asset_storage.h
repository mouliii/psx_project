#pragma once
#include <cstdint>
#include <cstring>
#include "graphics.h"
#include "cd_drive.h"
#include "texture.h"
#include "sound.h"

class AssetStorage
{
public:
    AssetStorage(CdDrive& cd, Graphics& gfx, std::uint16_t nTextures, std::uint16_t nSounds)
        :
        cd(cd),gfx(gfx)
    {
        textures = new Texture[nTextures];
        for (size_t i = 0; i < nTextures; i++)
        {
            texNames[i] = new char[9]{0};
        }
    }
    ~AssetStorage()
    {   // TODO
        // delete shit
    }
    Texture* LoadTexture(const char* fileName)
    {
        int16_t index = FindTexture(fileName);
        if (index != -1)
        {   puts("texture found!");
            return &textures[index];
        }
        else
        {   puts("texture loaded!");
            Texture* newTex = UploadTexture(fileName);
            return newTex;
        }
    }
    Texture* UploadTexture(const char* fileName)
    {   // upload data
        auto* data = cd.LoadFile(fileName);
        gfx.UploadTexture(data, &textures[curTexNum]);
        char newName[9] = {0};
        for (size_t i = 1; i < 9; i++)
        {
            if (fileName[i] == '\0')
            {
                newName[i] = fileName[i];
                break;
            }
            newName[i] = fileName[i];
        }
        std::strncpy(texNames[curTexNum], newName, 9);
        curTexNum++;
    }
private:
    int16_t FindTexture(const char* fileName)
    {
        for (std::uint16_t i = 0; i < curTexNum + 1; i++)
        {   // match
            if (std::strncmp(fileName, texNames[i], 8) == 0 )
            {
                return i;
            }
        }
        return -1;
    }

private:
    CdDrive& cd;
    Graphics& gfx;
    char* texNames[9];
    Texture* textures;
    uint16_t curTexNum = 0;
    //char* soundNames[9];
    //Sound* sounds;
};