#include "swantypes.h"
#include "gfl/core/gfl_heap.h"
#include "pml/poke_party.h"

struct PokeNick {
    HeapID heapID;
    u8 padding[2];
    PartyPkm* pkm;
    u8 unk1[0x34];
    u32 state;
    u32 yesNoDecision;
    u8 unk2[4];
    b32 isNsPkm;
    u8 unk3[4];
    u32 yesNoState;
    // ...
};

extern "C" {
    PokeNick* PokeNick_InitInner(HeapID, PartyPkm*, ...);
    void PokeNick_FreeInner(PokeNick*);
    u32 PokeNick_UpdateInner(PokeNick*);
}
