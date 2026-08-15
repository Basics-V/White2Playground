#include "MODS.h"
#include "swantypes.h"

#ifdef PERMADEATH
#include "Util.h"
#include "pml/pokeparty_decs.h"
extern "C" {
    // Don't revive at nurse joy/other full heals
    u32 THUMB_BRANCH_LINK_PokeParty_Recover_0xa(PartyPkm* targetPkm, PkmField field, void* extra) {
        u32 hp = PokeParty_GetParam(targetPkm, PF_NowHP, extra);

        // If the Pokémon isn't dead, fetch the max HP
        if (hp != 0) hp = PokeParty_GetParam(targetPkm, field, extra);
        return hp;
    }

    // Save fainted marker in (PkmField)0x72 (unused param?) when placing in box
    void* BoxSaveAccessor_GetMainSave(BoxSaveAccessor*);
    void* THUMB_BRANCH_LINK_BoxSaveAccessor_SetPkm_0xa(BoxSaveAccessor* BoxSaveAccessor, u32, u32, BoxPkm* targetPkm) {
        PokeParty* party = Mi4::GameSys()->m_GameData->m_Party;
        u32 PIDtoMatch = PML_PkmGetParamCore(targetPkm, PF_PID, NULL);
        for (int i = 0; i < party->PokemonCount; i++) {
            PartyPkm* pkm = &party->Pokemon[i];
            if (PokeParty_GetParam(pkm, PF_PID, NULL) == PIDtoMatch) {
                if (PokeParty_GetParam(pkm, PF_NowHP, NULL) == 0)
                    PokeParty_SetParam(pkm, (PkmField)0x72, true); // Unused(?) param
                break;
            }
        }
        return BoxSaveAccessor_GetMainSave(BoxSaveAccessor);
    }

    // Check for fainted marker when retrieving from box
    void THUMB_BRANCH_LINK_PokeParty_RecalcStatsCore_0x28c(PartyPkm* targetPkm, PkmField field, u32 hp) {
        // If the Pokémon is dead, reset the correct HP
        if (PokeParty_GetParam(targetPkm, (PkmField)0x72, NULL))
            hp = 0;

        // Apply the changes
        PokeParty_SetParam(targetPkm, field, hp);
    }
}
#endif
