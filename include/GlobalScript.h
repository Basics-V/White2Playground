#pragma once
#include "swantypes.h"

struct ScriptGlobalTableEntry {
    u16 startID;
    u16 endID;
    u16 scrDatID;
    u16 textArcID;
    u16 textDatID;
};

// Script table constant
extern ScriptGlobalTableEntry ScriptGlobalTable[];

extern "C" {
    u16 FieldScript_ResolveSCRID(u16, u16, u16*, u16*, u16*);
}
