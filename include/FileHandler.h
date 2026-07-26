#pragma once
#include "swantypes.h"

extern "C" {
    b32 ReadDataFromFile(const char*, u32, u8*, u32);
    u32 GetFileSize(const char*);
}
