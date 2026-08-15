#pragma once
#include "swantypes.h"
#include "gfl/core/gfl_heap.h"

struct StrBuf { // Paideieitor/PW2Code/Headers/defs.h
    u16 charCapacity;
    u16 charCount;
    u32 magic;
    u16 string[];
};

extern "C" {
    StrBuf* GFL_StrBufCreate(int, HeapID);
    void* GFL_MsgSysLoadData(bool, u16, u16, HeapID);
    void GFL_MsgDataLoadStrbuf(void*, int, StrBuf*);
    StrBuf* GFL_MsgDataLoadStrbufNew(void*, int);
    void GFL_MsgDataFree(void*);
    void GFL_StrBufFree(StrBuf*);
    void copyVarForText(void*, int, void*);
    void GFL_WordSetFormatStrbuf(void*, StrBuf*, StrBuf*);

    void* FieldMsg_NewMsgWin(void*, void*, int, u16, u16, u16, u16);
}
