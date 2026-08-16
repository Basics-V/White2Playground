#include "MODS.h"
#include "swantypes.h"
// PW2Code
#include "Headers/main_module.h"
#include "Headers/server_flow.h"

struct BattleStringSys {
    u8 unk1[0x10];
    void* msgData;
    // ...
};
static BattleStringSys* btlStrSys = (BattleStringSys*)0x21DD8BC;

#ifdef FIRST_ENCOUNTER
#include "FIRST_ENCOUNTER.h"
#include "data/heapid_def.h"
#include "Util.h"
extern "C" {
    BtlType THUMB_BRANCH_LINK_ServerControl_ThrowBallRoot_0x66(MainModule* mainModule) {
        if (is1stDone())
            return BtlType_Max;
        return MainModule_GetBattleType(mainModule);
    }

    void THUMB_BRANCH_LINK_ServerCommand_TrainerBlockBall_0x46(Btlv_StringParam* strParam, u32 narcIdx, u32 msgIdx) {
        if (is1stDone()) msgIdx = 0;
        Btlv_StringParam_Setup(strParam, narcIdx, msgIdx);
    }

    // redef b/c conflicting StrBuf in PW2Code
    void* GFL_MsgSysLoadData(bool, u16, u16, HeapID);
    void GFL_MsgDataFree(void*);
    void BtlvCore_StartMessage(BtlvCore*, Btlv_StringParam*);
    void THUMB_BRANCH_LINK_ServerCommand_TrainerBlockBall_0x50(BtlClientWk* btlClientWk, Btlv_StringParam* strParam) {
        void* msgData; bool isEnc = is1stDone();
        if (isEnc) {
            msgData = btlStrSys->msgData;
            btlStrSys->msgData = GFL_MsgSysLoadData(false, 2, ENC1_TXTDAT, btlClientWk->TrainerMsgHeapID);
        }
        BtlvCore_StartMessage(btlClientWk->btlvCore, strParam);
        if (isEnc) {
            GFL_MsgDataFree(btlStrSys->msgData);
            btlStrSys->msgData = msgData;
        }
    }
}
#endif
