#pragma once
#include <cstdint>
#include <psxcd.h>

class CdDrive
{
public:
    CdDrive();
    std::uint32_t* LoadFile(const char* fileName);
private:
};