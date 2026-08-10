#include "swantypes.h"
#include "pml/poke_party.h"

extern "C" u32 PokeParty_GetParam(PartyPkm*, PkmField, void*);
extern "C" void PokeParty_SetParam(PartyPkm*, PkmField, u32);
extern "C" u32 PML_PkmGetParamCore(BoxPkm*, PkmField, void*);
