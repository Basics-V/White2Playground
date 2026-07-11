namespace Mi4 {
#ifdef DEBUG
    void Printf(const char* format, ...);
#else
    inline void Printf(...);
#endif
}

#include "math/vector.h"
#include "swantypes.h"
extern "C" {
    void gfxTranslate(VecFx32*);
    void gfxClearDepth(u16);
    void GFL_G3DSysGetSwapBufferParams(b32*, b32*);
}
