#include "gamepad.h"

GamePad::GamePad()
{
    // first byte 0 if controller connected, second byte high bits controller type, low bits button data length
    padBuffer[0][0] = padBuffer[0][1] = 0xff;
    padBuffer[0][1] = padBuffer[1][1] = 0xff;
    InitPAD(padBuffer[0], 34, padBuffer[1], 34);
    StartPAD(); // start polling (TODO[SPI])
    ChangeClearPAD(0);
}

bool GamePad::IsControllerConnected(std::int8_t player)
{
    PADTYPE* pad = reinterpret_cast<PADTYPE*>(&padBuffer[player]);
    return pad->stat;
}

bool GamePad::IsButtonPressed(std::int8_t player, std::uint16_t button)
{
    //PADTYPE* pad = GetController(player);
    PADTYPE* pad = reinterpret_cast<PADTYPE*>(&padBuffer[player]);
    if(~pad->btn & button)
    {
        return true;
    }
    return false;
}
// https://thatgamesguy.co.uk/cpp-game-dev-5/
bool GamePad::IsButtonJustPressed(std::int8_t player, std::uint16_t button)
{
    //PADTYPE* pad = GetController(player);
    PADTYPE* pad = reinterpret_cast<PADTYPE*>(&padBuffer[player]);
    std::uint16_t pressed = ~pad->btn & button;
    if(~prevBtnState[player] & pressed)
    {
        wtf = true;
        return true;
    }
    wtf = false;
    return false;
}

PADTYPE* GamePad::GetController(std::int8_t player)
{
    PADTYPE* pad = reinterpret_cast<PADTYPE*>(&padBuffer[player]);
    pad->btn = ~pad->btn;
    return pad;
}

void GamePad::UpdateBuffer()
{
    for (std::uint8_t i = 0; i < 2; i++)
    {
        PADTYPE* pad = reinterpret_cast<PADTYPE*>(&padBuffer[i]);
        prevBtnState[i] = pad->btn;
    }
}
