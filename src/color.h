#pragma once
#include <cstdint>

//struct ColorElements
//{
//    uint8_t a = 0;
//    uint8_t r = 0;
//    uint8_t g = 0;
//    uint8_t b = 0;
//};

// ARGB
class Color
{
public:
    Color() {r = 128; g = 128; b = 128;};
    Color(uint8_t r, uint8_t g, uint8_t b)
    {
        SetColor(r,g,b);
    }
    void SetColor(uint8_t r, uint8_t g, uint8_t b)
    {
        color = r << 16 + g << 8 + b;
        this->r = r;
        this->g = g;
        this->b = b;
    }
public:
    uint32_t color = 0;// no alpha
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

};