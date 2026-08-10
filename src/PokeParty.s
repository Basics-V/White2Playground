.thumb
#include "MODS.h"

#ifdef NO_HEAL
@ Early return
FULL_COPY_PokeParty_Recover:
    BX LR
    .size FULL_COPY_PokeParty_Recover, . - FULL_COPY_PokeParty_Recover
#endif
