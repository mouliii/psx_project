#include "game_pad.h"
#include <cassert>

GamePad::GamePad()
{
    // first byte 0 if controller connected, second byte high bits controller type, low bits button data length
    padBuffer[0][0] = padBuffer[0][1] = 0xff;
    padBuffer[0][1] = padBuffer[1][1] = 0xff;
    InitPAD(padBuffer[0], 34, padBuffer[1], 34);
    StartPAD();
    ChangeClearPAD(0);
}

uint16_t GamePad::GetInput(uint8_t player)
{
    assert(player < 2);
    pad = reinterpret_cast<PADTYPE*>(&padBuffer[player]);
    return pad->btn;
}

PADTYPE *GamePad::GetPad(uint8_t player)
{
    pad = reinterpret_cast<PADTYPE*>(&padBuffer[player]);
    return pad;
}
