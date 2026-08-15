.thumb
#include "MODS.h"

#ifdef PERMADEATH
@ Don't allow revive-type items to be used
FULL_COPY_PokeList_CanItemWithBattleStatsBeUsed_0xfe:
    MOV R0,#0x0
    .size FULL_COPY_PokeList_CanItemWithBattleStatsBeUsed_0xfe, . - FULL_COPY_PokeList_CanItemWithBattleStatsBeUsed_0xfe

@ Let our custom rare candy check provide the return and safely dealloc stack
FULL_COPY_PokeList_CanItemWithBattleStatsBeUsed_0x148:
    MOV R1,R6
    .size FULL_COPY_PokeList_CanItemWithBattleStatsBeUsed_0x148, . - FULL_COPY_PokeList_CanItemWithBattleStatsBeUsed_0x148
FULL_COPY_PokeList_CanItemWithBattleStatsBeUsed_0x14e:
    ADD SP,#0x1C
    .size FULL_COPY_PokeList_CanItemWithBattleStatsBeUsed_0x14e, . - FULL_COPY_PokeList_CanItemWithBattleStatsBeUsed_0x14e
#endif
