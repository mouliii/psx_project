#pragma once
#include <psxgpu.h>
#include <cstdint>

class RenderBuffer
{
public:
    RenderBuffer(size_t ot_length, size_t buffer_length);
    ~RenderBuffer();
    void Setup(int x, int y, int w, int h, int r, int g, int b);
    uint8_t* BufferStart();
    uint8_t* BufferEnd();
    uint32_t* OTEntry(int z); // parempi nimi?
    void ClearOT();
    void Draw();
    void Display();
private:
    DISPENV dispEnv;
    DRAWENV drawEnv;
    uint32_t* ot;
    uint8_t* buffer;
    size_t otLength;
    size_t bufferLength;
    // size_t == uint == int32?
};