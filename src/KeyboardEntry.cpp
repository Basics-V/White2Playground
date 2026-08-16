#include "MODS.h"
#include "swantypes.h"
#include "gfl/core/gfl_heap.h"

struct KeyboardCallerData {
    u32 entrytype;
    // ...
};

struct KeyboardEntrySys {
    u8 unk1[0x2D8];
    KeyboardCallerData* callData;
    u8 unk2[4];
    void* profanityCheckWork;
    // ...
};

#ifdef FORCE_NICKNAME
extern "C" {
    b32 ProfanityCheck_CheckString(void*, u16*, HeapID);
    b32 THUMB_BRANCH_LINK_KeyboardEntry_Update_0x1d4(KeyboardEntrySys* entrySys, u16* string, HeapID heapID) {
        // If Pokémon nickname entry and no nickname is entered...
        if (entrySys->callData->entrytype == 1 && string[0] == 0xFFFF)
            return true; // ...then don't proceed to the next screen
        return ProfanityCheck_CheckString(entrySys->profanityCheckWork, string, heapID);;
    }
}
#endif
