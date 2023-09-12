#pragma once
#include <psxpad.h> // enum defs
#include <psxapi.h>

class GamePad
{
public:
    GamePad();
    uint16_t GetInput(uint8_t player);
    PADTYPE* GetPad(uint8_t player);
private:
    PADTYPE* pad;
    uint8_t padBuffer[2][34] = {0};
};