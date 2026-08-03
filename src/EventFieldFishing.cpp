#include "swantypes.h"
#include "FieldEncount.h"
#include "Util.h"

struct EventFieldFish {
    u8 unk1[12];
    EncountSystem* encSys;
    void* recordWork;
    u8 unk2[69];
    u8 encType;
    u8 unk3[6];
    u32 frame;
    void* btlSetup;
    // ...
};

#ifdef FISHING_CONVENIENT
#ifdef FISHING_NO_WAIT
#error Please choose either FISHING_NO_WAIT or FISHING_CONVENIENT, not both!
#endif

#include "nds/hid.h"
#include "system/game_input.h"
extern "C" {
    u32 FieldFishing_AwaitInput(EventFieldFish*, u32);
    void RecordAddOne(void*, u32);
    void FieldFishing_BobberDestroy(EventFieldFish*);
    void EncountSystem_CancelPhenomenon(EncountSystem*);
    void BtlSetup_Free(void*);
}

extern "C" {
    u32 THUMB_BRANCH_LINK_EventFieldFishing_Callback_0xc0(EventFieldFish* fieldFishWork, u32 frames) {
        if (GCTX_HIDGetPressedKeys() & KEY_B)
            return 3;

        return FieldFishing_AwaitInput(fieldFishWork, frames);
    }

    u32 THUMB_BRANCH_LINK_EventFieldFishing_Callback_0x120(EventFieldFish* fieldFishWork, u32 inputRet) {
        RecordAddOne(fieldFishWork->recordWork, 0x50);

        if (inputRet == 3) {
            FieldFishing_BobberDestroy(fieldFishWork);
            if (fieldFishWork->btlSetup != NULL) {
                if (fieldFishWork->encType == PHENOMENON)
                    EncountSystem_CancelPhenomenon(fieldFishWork->encSys);
                BtlSetup_Free(fieldFishWork->btlSetup);
            }
            return 8;
        }
        return 4;
    }
}
#endif
