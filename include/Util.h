#pragma once

#include "system/gamesystem.h"

#ifdef __cplusplus
namespace Mi4 {
#ifdef DEBUG
    void Printf(const char* format, ...);
#else
    static inline void Printf(...) {}
#endif
}
#else
C_DECL_BEGIN
#ifdef DEBUG
void Mi4_Printf(const char* format, ...);
#else
static inline void Mi4_Printf(...) {}
#endif
C_DECL_END
#endif

#define ALIAS(alias, target) \
    __asm__(".globl " #alias "\n\t.equ " #alias ", " #target);

#include "math/vector.h"
#include "swantypes.h"
C_DECL_BEGIN
void gfxTranslate(VecFx32*);
void gfxClearDepth(u16);
void GFL_G3DSysGetSwapBufferParams(b32*, b32*);
C_DECL_END

#include "field/script.h"
C_DECL_BEGIN
void GFL_SndSEPlay(u32);
C_DECL_END
