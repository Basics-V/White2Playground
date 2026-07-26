#include "swantypes.h"
#include "system/game_data.h"
#include "save/savedata_eventwork.h"

extern "C" {
    EventWorkSave* GameData_GetEventWork(GameData*); // Technically system/game_data.h
    u16* EventWork_GetWkPtr(EventWorkSave*, int);
    bool EventWork_FlagGet(EventWorkSave*, int);
}
