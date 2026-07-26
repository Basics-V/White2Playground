#pragma once

namespace Mi4 {
#ifdef DEBUG
    void Printf(const char* format, ...);
#else
    inline void Printf(...) {}
#endif
}

#include "math/vector.h"
#include "swantypes.h"
extern "C" {
    void gfxTranslate(VecFx32*);
    void gfxClearDepth(u16);
    void GFL_G3DSysGetSwapBufferParams(b32*, b32*);
}

#include "system/gamesystem.h"
static GameSystem* gameSys = *(GameSystem**)0x2141134;

#include "gfl/str/string.h"
#include "field/script.h"
extern "C" {
    StrBuf* GFL_StrBufCreate(int, HeapID);
    void* GFL_MsgSysLoadData(u8, u16, u16, HeapID);
    void GFL_MsgDataLoadStrbuf(void*, int, StrBuf*);
    void GFL_MsgDataFree(void*);
    void GFL_StrBufFree(StrBuf*);
    void copyVarForText(void*, int, void*);
    void GFL_WordSetFormatStrbuf(void*, StrBuf*, StrBuf*);

    void* FieldMsg_NewMsgWin(void*, void*, int, u16, u16, u16, u16);    

    void GFL_SndSEPlay(u32);

    ScriptVM* EventScriptCall_Start(GameEvent*, u16, FieldActor*, void*, HeapID);
}
