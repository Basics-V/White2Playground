#include "swantypes.h"

struct StrBuf { // Paideieitor/PW2Code/Headers/defs.h
    u16 charCapacity;
    u16 charCount;
    u32 magic;
    u16 string[];
};
