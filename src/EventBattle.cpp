#include "MODS.h"
#include "battle/btl_result.h"

#ifdef FIRST_ENCOUNTER
#include "FIRST_ENCOUNTER.h"
#include "field/field_eventwork.h"
extern "C" {
    BattleResult GameData_GetLastBtlResult(GameData*);
    BattleResult THUMB_BRANCH_LINK_EventWildBattleCall_Callback_0xb0(GameData* gameData) {
        u16 zoneID = gameData->m_PlayerState.ZoneID;
        *EventWork_GetWkPtr(gameData->m_EventWork, FIRST_ENCOUNTER_VARS[getZoneVar(zoneID)]) |= getZoneBit(zoneID);
        return GameData_GetLastBtlResult(gameData);
    }
}
#endif
