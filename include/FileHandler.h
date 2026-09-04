#pragma once
#include "swantypes.h"

C_DECL_BEGIN
b32 ReadDataFromFile(const char*, u32, u8*, u32);
u32 GetFileSize(const char*);
C_DECL_END
