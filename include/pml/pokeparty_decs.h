#include "swantypes.h"
#include "pml/poke_party.h"

C_DECL_BEGIN
u32 PokeParty_GetParam(PartyPkm*, PkmField, void*);
void PokeParty_SetParam(PartyPkm*, PkmField, u32);
u32 PML_PkmGetParamCore(BoxPkm*, PkmField, void*);
C_DECL_END
