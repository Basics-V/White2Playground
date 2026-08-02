#include "Util.h"
#include "Bag.h"
#include "swantypes.h"
#include "FieldAction.h"

#ifdef CUSTOM_ITEM_USE
#include "CUSTOM_ITEM_USE.h"
#include "system/game_event.h"
#include "nds/mem.h"
#endif

struct FieldActionWork {
    u8 unk1[0x44];
    BagActionID bagActionID;
    u32 itemID;
    // ...
};

#ifdef CUSTOM_ITEM_USE
extern "C" {
    u32 EventFieldBag_HandleReturnAction(void*, FieldActionWork*);
    u32 EventFieldBag_HookReturnAction(void* FieldActionSys, FieldActionWork* actionData) {
        // Check if it's our custom BagActionID
        if (actionData->bagActionID == BAG_CUSTOM) {
            for (CustomItemUseDef* def = customItemUseDefs; def->func != NULL; def++) {
                if (def->ID == actionData->itemID) {
                    *(u32*)(*(int*)(FieldActionSys + 0x18) + 0x2c) = def->ID + FieldCommonEventTableMax;
                    return 3; // Use item in field
                }
            }
        }
        return EventFieldBag_HandleReturnAction(FieldActionSys, actionData);
    }
}

u32 (*FULL_COPY_FIELD_PROC_LINK_LIST_0x3c)(void*, FieldActionWork*) = (u32 (*)(void*, FieldActionWork*))EventFieldBag_HookReturnAction;

extern "C" PlayerState* GameData_GetPlayerState(GameData*);
extern "C" {
    GameEvent* THUMB_BRANCH_CallFieldCommonEventFunc(u32 eventType, GameSystem* gameSys, Field* field) {
        // Check if we are calling a custom field common event
        if (eventType >= FieldCommonEventTableMax) {
            eventType -= FieldCommonEventTableMax;
            for (CustomItemUseDef* def = customItemUseDefs; def->func != NULL; def++)
                if (def->activate != NULL && def->ID == eventType)
                    return def->activate(field, gameSys);

            // Could not find it?
            Mi4::Printf("WARNING: Could not find a CUSTOM_ITEM_USE def that matches eventType!\n");
            return NULL;
        }
        #ifdef PW2CODE_INFINITE_REPEL
        if (eventType == FieldCommonEventInfiniteRepel)
            return EventFieldToggleRepel_Create(field, gameSys);
        #endif
        return FIELD_COMMON_EVENTS[eventType].func(field, gameSys);
    }
}
#endif
