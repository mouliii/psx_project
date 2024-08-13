#include "controller.h"

Controller::Controller()
{
    padBuffer[0] = padBuffer[1] = 0xff;
    pad = reinterpret_cast<PADTYPE*>(&padBuffer);
}

PADTYPE *Controller::GetController()
{
    //PADTYPE* pad = reinterpret_cast<PADTYPE*>(&padBuffer);
    return pad;
}

void Controller::UpdateBuffer()
{
    padPrevBuffer = ~pad->btn;
}


bool Controller::IsControllerConnected()
{
    if (pad->stat == 1){
        return false;
    }
    if (pad->type != PAD_ID_ANALOG){
        return false;
    }
    return  true;
    //if (pad->stat == 0)
    //{
    //    return true;
    //}
    //return false;
}

bool Controller::IsButtonPressed(std::uint16_t button)
{
    return ~pad->btn & button;
}

bool Controller::IsButtonJustPressed(std::uint16_t button)
{   // pressed this frame and not pressed last frame
    std::uint16_t pressed = ~pad->btn & button;
    return pressed & ~padPrevBuffer;
}

bool Controller::IsButtonJustReleased(std::uint16_t button)
{   // not pressed this frame and pressed last frame
    std::uint16_t notPressed = pad->btn & button;
    return notPressed & padPrevBuffer;
}
int8_t Controller::GetLeftAnalogX()
{
    if (pad->type == PAD_ID_ANALOG_STICK || pad->type == PAD_ID_ANALOG)
    {
        int8_t val = static_cast<int8_t>(pad->ls_x-128);
        if (abs(val) > deadZone)
        {
            return val;
        }
    }
    return 0;
}
int8_t Controller::GetLeftAnalogY()
{
    if (pad->type == PAD_ID_ANALOG_STICK || pad->type == PAD_ID_ANALOG)
    {
        int8_t val = static_cast<int8_t>(pad->ls_y-128);
        if (abs(val) > deadZone)
        {
            return val;
        }
    }
    return 0;
}
int8_t Controller::GetRightAnalogX()
{
    if (pad->type == PAD_ID_ANALOG_STICK || pad->type == PAD_ID_ANALOG)
    {
        int8_t val = static_cast<int8_t>(pad->rs_x-128);
        if (abs(val) > deadZone)
        {
            return val;
        }
    }
    return 0;
}
int8_t Controller::GetRightAnalogY()
{
    if (pad->type == PAD_ID_ANALOG_STICK || pad->type == PAD_ID_ANALOG)
    {
        int8_t val = static_cast<int8_t>(pad->rs_y-128);
        if (abs(val) > deadZone)
        {
            return val;
        }
    }
    return 0;
}
// upper 8 bits x-axis lower 8 y-axis | return left stick if true else right
uint16_t Controller::GetAnalogInputRaw(bool left)
{
    if (pad->type == PAD_ID_ANALOG_STICK || pad->type == PAD_ID_ANALOG)
    {
        uint16_t buffer = 0;
        if (left)
        {
            buffer = pad->ls_x;
            buffer <<= 8;
            buffer |= pad->ls_y;
            return buffer;
        }
        else
        {
            buffer = pad->rs_x;
            buffer <<= 4;
            buffer |= pad->rs_y;
            return buffer;
        }
    }
    return 0;
}