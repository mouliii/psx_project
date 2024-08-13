#include "cd_drive.h"
#include "debug_msg.h"

CdDrive::CdDrive()
{
    // Init CD-ROM library
    CdInit();
}

// filename in CAPS -> "\\AWESOME.TIM;1"
std::uint32_t *CdDrive::LoadFile(const char *fileName)
{
    CdlFILE	file;
    std::uint32_t* buffer;

    if (CdSearchFile(&file, fileName))
    {
        std::uint32_t nSectors = (file.size + 2047) / 2048;
        buffer = new std::uint32_t[2048 * nSectors];
        // Set seek target (seek actually happens on CdRead())
        CdControl(CdlSetloc, &file.pos, 0);
        CdRead(nSectors, buffer, CdlModeSpeed);
        // Wait until read has completed
        CdReadSync(0, 0);
        return buffer;
    }
    char str[50];
    sprintf(str, "failed to load: %s", fileName);
    DEBUG_MSG::CreateMsg(0,str);
    return nullptr;
}
