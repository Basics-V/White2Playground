#include "Util.h"
#include "field/field_eventwork.h"
#include "field/field_encount.h"
#include "swantypes.h"

#define PHENOM_STEP_MAX_VAR 0x4096 // X steps until we reroll
#define PHENOM_STEP_RND_VAR 0x409A // 1/Y chance for phenomenon

#ifdef PHENOM_RAND_MAN
#include "gfl/core/gfl_random.h"
extern "C" {
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

#ifdef PHENOM_POKERADAR
#include "PHENOM_POKERADAR.h"
extern "C" {
    u16 Field_GetPlayerStateZoneID(Field*);
    u8 GameData_GetSeason(GameData*);
    u32 GetMapBGMIDByPlayerState(GameData*, u16, u8);
    GameEvent* EventBGMChange_Create(GameSystem*, u32, u16, u16);
    FieldSoundSystem* GameData_GetFieldSoundSystem(GameData*);
    void FieldSnd_ResumeAmbience(FieldSoundSystem*, int);
    void EncountSystem_CancelPhenomenon(EncountSystem*);
    void EncountSystem_CancelPhenomenonCore(EncountSystem*, void*);
    FieldPlayer* Field_GetPlayer(Field*);
    void RestartBGM(GameSystem* gameSys, u16 fadeOut, u16 fadeIn) {
        u16* radarWk = EventWork_GetWkPtr(gameSys->m_GameData->m_EventWork, PHPKRDR_EVTWK);
        if (*radarWk == 1) {
            /* References s009E_BGMChangeMap */
            FieldSoundSystem* fldSndSys = GameData_GetFieldSoundSystem(gameSys->m_GameData);
            u16 zoneID = Field_GetPlayerStateZoneID(gameSys->m_Field);
            u8 season = GameData_GetSeason(gameSys->m_GameData);
            u32 bgmID = GetMapBGMIDByPlayerState(gameSys->m_GameData, zoneID, season);

            GameEvent_RunCallback(EventBGMChange_Create(gameSys, bgmID, fadeOut, fadeIn));
            FieldSnd_ResumeAmbience(fldSndSys, 2);

            *radarWk = 4;
        }
    }

    // When cancelling a phenomenon normally (NPCs, Poké Radar, etc...)
    void THUMB_BRANCH_EncountSystem_CancelPhenomenon(EncountSystem* encSys) {
        RestartBGM(encSys->m_GameSystem, 0x5A, 0x3C);
        EncountSystem_CancelPhenomenonCore(encSys, encSys->m_EffectEncountState);
    }

    // Force random events to go through our code
    void THUMB_BRANCH_LINK_CreateRandomPhenomenonEvent_0xe2(EncountSystem* encSys) {
        EncountSystem_CancelPhenomenon(encSys);
    }
    void THUMB_BRANCH_LINK_CreateRandomPhenomenonEvent_0xd0(EncountSystem* encSys) {
        EncountSystem_CancelPhenomenon(encSys);
    }
    FieldPlayer* THUMB_BRANCH_LINK_CreateRandomPhenomenonEvent_0x10a(Field* field) {
        RestartBGM(field->m_GameSystem, 0, 0);
        return Field_GetPlayer(field);
    }
}
#endif
