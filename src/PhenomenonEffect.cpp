#include "Util.h"
#include "swantypes.h"

#define PHENOM_STEP_MAX_VAR 0x4096 // X steps until we reroll
#define PHENOM_STEP_RND_VAR 0x409A // 1/Y chance for phenomenon

#ifdef PHENOM_RAND_MAN
#include "field/field_encount.h"
#include "gfl/core/gfl_random.h"
extern "C" {
    u16* EventWork_GetWkPtr(EventWorkSave*, int);

    // Update the minimum phenomenon step counter
    b32 THUMB_BRANCH_LINK_UpdatePhenomenon_0xb8(EncountState* encState, GameData* gameData) {
        // Increment step counter
        if (encState->field_14 != 0xffffffff) encState->field_14++;

        // Fetch our public max step var
        u16 stepMax = *EventWork_GetWkPtr(gameData->m_EventWork, PHENOM_STEP_MAX_VAR);

        /* Missing: PassPower_ApplyExploring */

        // Return if it is within our current step count
        return stepMax <= encState->field_14;
    }

    /*
        Our 1/VAR random chance
        Missing: PassPower_ApplyExploringChance
    */
    u32 THUMB_BRANCH_LINK_UpdatePhenomenon_0xc4(GameSystem* gameSys) {
        // Fetch our public random var
        return *EventWork_GetWkPtr(gameSys->m_GameData->m_EventWork, PHENOM_STEP_RND_VAR);
    }
    u32 THUMB_BRANCH_LINK_UpdatePhenomenon_0xce(GameSystem* gameSys) {
        // Fetch our public random var
        u16 randomDenominator = *EventWork_GetWkPtr(gameSys->m_GameData->m_EventWork, PHENOM_STEP_RND_VAR);

        // Gen random num w/ max randomDenominator
        return GFL_RandomLCAlt(randomDenominator) + 2; // + 2 is intentional
    }
}
#endif
