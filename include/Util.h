#pragma once

#include "system/gamesystem.h"
namespace Mi4 {
#ifdef DEBUG
    void Printf(const char* format, ...);
#else
    inline void Printf(...) {}
#endif
    inline GameSystem* GameSys() { return *(GameSystem**)0x2141134; };
}

#define ALIAS(alias, target) \
    __asm__(".globl " #alias "\n\t.equ " #alias ", " #target);

#include "math/vector.h"
#include "swantypes.h"
extern "C" {
    void gfxTranslate(VecFx32*);
    void gfxClearDepth(u16);
    void GFL_G3DSysGetSwapBufferParams(b32*, b32*);
}

#include "field/script.h"
extern "C" {
    void GFL_SndSEPlay(u32);
}
