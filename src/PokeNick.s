.thumb
#include "MODS.h"

#ifdef FORCE_NICKNAME
@ PokeNick->state = 2 (enter nickname)
FULL_COPY_PokeNick_InitInner_0x48:
    MOV R0,#0x2
    .size FULL_COPY_PokeNick_InitInner_0x48, . - FULL_COPY_PokeNick_InitInner_0x48

@ PokeNick->yesNoDecision = 1 (Yes)
FULL_COPY_PokeNick_InitInner_0x4c:
    MOV R0,#0x1
    .size FULL_COPY_PokeNick_InitInner_0x4c, . - FULL_COPY_PokeNick_InitInner_0x4c
#endif
