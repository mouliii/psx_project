#pragma once
#include <stdint.h>
#include "graphics.h"
#include "cd_drive.h"
#include "texture.h"
#include "sound.h"

// BROKEN; DO NOT USE; 

// inner template class <type-error> bullshit
template <typename T>
class Ref
{
public:
    Ref();
    Ref(T* data) :data(data){}
    ~Ref(){delete data;}
    void UnRef();
public:
    T* data = nullptr;
    std::uint16_t refCount = 0;
    char name[9]; // string termination
};

class AssetManager
{
public:
    AssetManager(CdDrive& cd, Graphics& gfx);
    Ref<Texture>* LoadTexture(const char* name);
private:
    template <typename T>
    T* FindAsset(const char* name);
    template <typename T>
    void CreateRef(Ref<T>* data);
    template <typename T>
    void DeleteRef(Ref<T>* data);
    template <typename T>
    void UnRef(Ref<T>* data);
private:
    static constexpr int nAssets = 16;
    CdDrive& cd;
    Graphics& gfx;
    uint8_t nextTexSpot = 0;
    Ref<Texture> textures[nAssets];
    uint8_t nextSoundSpot = 0;
    Ref<Sound> sounds[nAssets];
};

