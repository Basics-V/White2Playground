#pragma once
#include "MODS.h"
#include "Util.h"

#ifdef FIRST_ENCOUNTER
#include "system/game_data.h"
#include "field/field_eventwork.h"
static const u16 FIRST_ENCOUNTER_VARS[CAP_VAR_MAX] = {
    16529,
    16530,
    16531,
    16533,
    16534,
    16538,
    16546,
    16559,
    16560,
    16565,
    16567,
    16568,
    16583,
    16654,
    16655,
    16674,
    16701,
    16707,
    16708,
    16726,
    16727,
    16728,
    16729,
    16730,
    16731,
    16732,
    16733,
    16734,
    16735,
    16737,
    16739,
    16759,
    16762,
    16768,
    16769,
    16777,
    16779,
    16784,
    16785,
};

inline int getZoneVar(u16 idx) {
    return idx >> 4;
}

inline int getZoneBit(u16 idx) {
    while (idx >= 16) idx -= 16;
    return idx;
}

inline bool is1stDone() {
    GameData* gameData = Mi4::GameSys()->m_GameData;
    u16 zoneID = gameData->m_PlayerState.ZoneID;
    return (*EventWork_GetWkPtr(
        gameData->m_EventWork,
        FIRST_ENCOUNTER_VARS[getZoneVar(zoneID)]
    ) & getZoneBit(zoneID)) != 0;
}
#endif
