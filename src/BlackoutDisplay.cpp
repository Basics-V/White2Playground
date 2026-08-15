#include "MODS.h"
#include "swantypes.h"
#include "gfl/core/gfl_procsys.h"
#include "BlackoutDisplay.h"

#ifdef PARTY_KILL
#include "field/field_eventwork.h"
#include "gfl/str/string.h"
#include "gfl/hid.h"
#include "Util.h"
extern "C" {
    GameEvent* SaveDataWriteCore(GameSystem*, u16*);
    void GameData_QueueSave(GameData*);
    u32 GameData_ExecSave(GameData*);

    // Handle saving our TPK flag
    b32 BlackoutDisplayProc_Init_Wrapper(GameProc* proc, u32* state, void* initData, void* procData) {
        GameData* gameData = Mi4::GameSys()->m_GameData;
        EventWorkSave* eventWork = gameData->m_EventWork;

        // Set the TPK flag and begin our save process
        if (!EventWork_FlagGet(eventWork, TPK_FLAG)) {
            EventWork_FlagSet(eventWork, TPK_FLAG);
            GameData_QueueSave(gameData);
            u32 ret = 0;
            while (ret != 2 && ret != 3)
                ret = GameData_ExecSave(gameData);
        }

        // Handle standard blackout initialization procedure
        return BlackoutDisplayProc_Init(proc, state, initData, procData);
    }

    // Use our updated textfile
    void* THUMB_BRANCH_LINK_BlackoutDisplayProc_Update_0x68(bool preload, u16 arcID, u16 datID, HeapID heapID) {
        return GFL_MsgSysLoadData(preload, arcID, TPK_TXTDAT, heapID);
    }

    // Handle saving our TPK flag
    b32 BlackoutDisplayProc_End_Wrapper(GameProc* proc, u32* state, void* initData, void* procData) {
        b32 ret = BlackoutDisplayProc_End(proc, state, initData, procData);
        GFL_HIDDoSoftReset(0);
        return ret;
    }
}

// Insert our partykill handler
GameProcFunc FULL_COPY_BLACKOUT_DISPLAY_PROC_LIST_0x0 = &BlackoutDisplayProc_Init_Wrapper;
GameProcFunc FULL_COPY_BLACKOUT_DISPLAY_PROC_LIST_0x8 = &BlackoutDisplayProc_End_Wrapper;
#endif
