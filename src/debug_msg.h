#pragma once
#include <cstdint>
#include <cstring>
#include <cstdarg>
#include "graphics.h"

typedef struct
{
    char msg[50]{0};
    //int16_t showTime = 0;
    //int16_t timer = 0;
    // bool? active?
}DB_MSG;

class DEBUG_MSG
{
public:
    DEBUG_MSG(const DEBUG_MSG&) = delete;
    static DEBUG_MSG& Get()
    {
        static DEBUG_MSG instance;
        return instance;
    }
    static void Setup(Graphics* gfx, int16_t bufferLen){Get().ISetup(gfx,bufferLen);}
    static void CreateMsg(int16_t time,const char* msg){Get().ICreateMsg(time, msg);};
    //static void CreateMsg(const char* msg...){Get().ICreateMsg(msg);};
    static void ShowMessages() {Get().IShowMessages();};
private:
    void ISetup(Graphics* gfx, int16_t bufferLen)
    {
        this->gfx = gfx;
        bufLen = bufferLen;
        msgs = new DB_MSG[bufferLen];
    }
    void ICreateMsg(int16_t time,const char* msg)
    {
        std::memmove(&msgs[1], &msgs[0], sizeof(DB_MSG)*(bufLen-1));
        std::strncpy(msgs[0].msg, msg, 50);
    }
    //void ICreateMsg(const char* fmt)
    //{
    //    va_list args;
    //    va_start(args, fmt);
    //    std::memmove(&msgs[1], &msgs[0], sizeof(DB_MSG)*(bufLen-1));
    //    std::strncpy(msgs[0].msg, msg, 50);
    //}
    void DeleteMsg(int8_t index);
    void SortArray();
    void IShowMessages()
    {
        int16_t x;
        int16_t y;
        for (int16_t i = 0; i < bufLen; i++)
        {
            if (msgs[i].msg[0] != 0)
            {
                gfx->DrawText(5, 230 - i*10, 0, msgs[i].msg);
            }
            else
            {
                break;
            }
        }
        
    }

    DEBUG_MSG(){}
    DB_MSG* msgs;
    int16_t bufLen;
    Graphics* gfx;
};