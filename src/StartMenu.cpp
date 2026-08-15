#include "MODS.h"
#include "swantypes.h"
#include "gfl/str/string.h"
#include "data/trainer.h"

struct StartMenu {
    u8 unk1[4];
    TrainerCard* trainerCard;
    u8 unk2[0x70];
    void* msgData;
    u8 unk3[4];
    StrBuf* strBuf;
    u8 unk4[0xf7];
    u32 innerState;
    u8 unk5[0x11];
    u32 state;
};

#ifdef PARTY_KILL
#define IS_PKILL() (EventWork_FlagGet(getConstDataBlock(SaveControl_GetInstance()), TPK_FLAG))
#define PKILL_NOTICE L"DEAD"
#include "gfl/core/gfl_overlay.h"
#include "data/heapid_def.h"
#include "save/save_control.h"
#include "field/field_eventwork.h"
#include "Util.h"
extern "C" {
    void StartMenu_DispMsgWin(StartMenu*, u32);
    b32 StartMenu_AwaitMsgDisp(StartMenu*);
    SaveControl* SaveControl_GetInstance();
    EventWorkSave* getConstDataBlock(SaveControl*);
    bool IsCGearUnlocked(void*);
    int YesNoUI_AwaitDecision(void*);

    // SaveData_Delete
    void SaveOutside_ClearData(HeapID);
    void DeleteDreamRadarSaveData(HeapID);
    void SaveControl_Delete(SaveControl*);
    int loadExtraSaveBlk(SaveControl*, int, HeapID);
    void clearExtraSaveBlk(SaveControl*, int, HeapID);
    void freeIntermediateSaveExtraBlksAfterLoad(SaveControl*, int);
    void sys_reset(int);

    StrBuf* THUMB_BRANCH_LINK_StartMenu_InitBmpWin_0x7e(void* msgData, u32 line) {
        bool pKill = IS_PKILL();
        if (pKill) {
            msgData = GFL_MsgSysLoadData(false, 2, TPK_TXTDAT, HEAPID_STARTMENU);
            line = 5;
        }
        StrBuf* strBuf = GFL_MsgDataLoadStrbufNew(msgData, line);
        if (pKill) GFL_MsgDataFree(msgData);
        return strBuf;
    }

    // Load our string into the name slot
    void THUMB_BRANCH_LINK_StartMenu_InitBmpWin_0xc8(void* wordSetSystem, int var, TrainerCard* trainerCardWork) {
        if (IS_PKILL()) {
            int i;
            for (i = 0; PKILL_NOTICE[i] != L'\0'; i++)
                trainerCardWork->string[i] = PKILL_NOTICE[i];
            trainerCardWork->string[i] = -1;
        }
        copyVarForText(wordSetSystem, var, trainerCardWork);
    }

    // Sneakpeak failed nuzlocke
    Gender THUMB_BRANCH_LINK_StartMenu_InitBmpWin_0xdc(TrainerCard* trainerCardWork) {
        if (IS_PKILL()) return FEMALE;
        return getTrainerGender(trainerCardWork);
    }

    // Skip the pre-CGear-unlocked condition if it is a failed nuzlocke
    bool THUMB_BRANCH_LINK_StartMenu_ContinueState_0x3e(void* work) {
        if (IS_PKILL()) return true;
        return IsCGearUnlocked(work);
    }

    // Ask to delete save file if it is a failed nuzlocke
    void THUMB_BRANCH_LINK_StartMenu_ContinueState_0x7a(StartMenu* startMenuWork, u32 line) {
        if (IS_PKILL()) {
            GFL_MsgDataFree(startMenuWork->msgData);
            startMenuWork->msgData = GFL_MsgSysLoadData(false, 2, TPK_TXTDAT, HEAPID_STARTMENU);
            line = 4;
        }
        StartMenu_DispMsgWin(startMenuWork, line);
    }

    // Delete if yes, Soft-Reset either way
    int THUMB_BRANCH_LINK_StartMenu_ContinueState_0x94(void* yesNoWinWork) {
        int decision = YesNoUI_AwaitDecision(yesNoWinWork);
        if (IS_PKILL()) {
            switch (decision) {
                case 0: { // Yes
                    // References SaveDataErase_DeleteFile() / OVL_162:0x21a0f55
                    // HEAPID_SAVEDATA_DELETE -> HEAPID_STARTMENU
                    SaveControl* savCtrl = SaveControl_GetInstance();
                    GFL_OvlLoad(331);
                    SaveOutside_ClearData(HEAPID_STARTMENU);
                    GFL_OvlUnload(331);
                    DeleteDreamRadarSaveData(HEAPID_STARTMENU);
                    SaveControl_Delete(savCtrl);
                    for (int idx = 0; idx < 0x15; idx++) {
                        if (loadExtraSaveBlk(savCtrl, idx, HEAPID_STARTMENU) == 1)
                            clearExtraSaveBlk(savCtrl, idx, HEAPID_STARTMENU);
                        freeIntermediateSaveExtraBlksAfterLoad(savCtrl, idx);
                    }
                }
                // Fallthrough
                case -2: // No
                    sys_reset(0);
            }
        }
        return decision;
    }
}
#endif
