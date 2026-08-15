#include "MODS.h"
#include "swantypes.h"

#ifdef PERMADEATH
#include "pml/pokeparty_decs.h"
#include "gfl/core/gfl_heap.h"
extern "C" {
    // Handle whether a rare candy can be used on a party member
    b32 THUMB_BRANCH_LINK_PokeList_CanItemWithBattleStatsBeUsed_0x14a(void* heap, PartyPkm* targetPkm) {
        GFL_HeapFree(heap);
        return PokeParty_GetParam(targetPkm, PF_NowHP, NULL) != 0;
    }
}
#endif
