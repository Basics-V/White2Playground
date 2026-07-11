#include "Util.h"

#ifdef DEBUG
#include <cstdarg>
#include <cstdio>
#ifdef MELONDS
    #define DEBUG_PREFIX "~ "
    // stdbuf -oL ./melonDS | sed -unE "/abort/p; s/^~ //p"
#endif
namespace Mi4 {
    /*
        Reimplementation of k::Printf in Hello007/NitroKernel
    */
    void Printf_Core(const char* str) {
        #if defined DESMUME
            // https://wiki.desmume.org/index.php?title=Faq
            asm volatile ("MOVS R0, %0" : : "r" (str));
            asm volatile ("SWI #0xFC");
        #elif defined MELONDS
            // https://problemkaputt.de/gbatek-ds-debug-registers-emulator-devkits.htm
            char* nocashCharOut = (char*)0x4FFFA1C;
            while (*str) {
                *nocashCharOut = *str;
                #ifdef DEBUG_PREFIX
                    if (*str == '\n' && *(str + 1)) {
                        Printf_Core(DEBUG_PREFIX);
                    }
                #endif
                str++;
            }
        #endif
    }

    // HelloOO7/NitroKernel/src/kPrint.cpp
    void Printf(const char* format, ...) {
        #ifdef DEBUG_PREFIX
            Printf_Core(DEBUG_PREFIX);
        #endif
        va_list args;
        va_start(args, format);
        char outBuffer[256];
        vsnprintf(outBuffer, 256, format, args);
        Printf_Core(outBuffer);
        va_end(args);
    }
}
#endif

#include "gfl/fs/gfl_archive.h"
#include "gfl/g3d/gfl_g3d_system.h"
extern "C" {
    // https://problemkaputt.de/gbatek.htm#ds3dmatrixloadmultiply
    void gfxTranslate(VecFx32* offset) {
        fx32* MTX_TRANS = (fx32*)0x4000470;
        *MTX_TRANS = offset->x;
        *MTX_TRANS = offset->y;
        *MTX_TRANS = offset->z;
    }

    // https://problemkaputt.de/gbatek.htm#ds3drearplane
    void gfxClearDepth(u16 depth) {
        u16* CLEAR_DEPTH = (u16*)0x4000354;
        *CLEAR_DEPTH = depth;
    }

    // https://problemkaputt.de/gbatek.htm#ds3ddisplaycontrol for details, but implementation is GF's G3DSystem
    // References GFL_G3DSysSetSwapBufferParams/ARM9:0x2049241
    void GFL_G3DSysGetSwapBufferParams(b32* useManualAlphaSort, b32* depthBufferW) {
        G3DSystem* g3dSys = (G3DSystem*)(*(int*)0x2141964 + 0xC);

        if (useManualAlphaSort != NULL) *useManualAlphaSort = g3dSys->UseManualAlphaSort;
        if (depthBufferW != NULL)       *depthBufferW = g3dSys->DepthBufferW;
    }
}
