/*
    A massive thank you to Paideieitor
    and his PW2Code for the indispensable
    research on the Bag and the ShortcutMenu!
    You can find his project here:
    https://github.com/Paideieitor/PW2Code
*/
#include "MODS.h"
// White2Playground
#include "Util.h"
#include "FieldAction.h"
// Paideieitor/PW2Code/*
#include "settings.h"
#include "Headers/items.h"
#include "Headers/shortcut_menu.h"
#include "Headers/bag.h"

#ifdef CUSTOM_ITEM_USE
#ifdef CUSTOM_SHORTCUT_TXT
#define ShortcutMenu_CustomTxtDat 768
#define ShortcutMenu_ItemMsg_Max  33
extern "C" {
    void* GFL_MsgSysLoadData(u8, u16, u16, HeapID);
    void GFL_MsgDataFree(void*);
}
#endif

struct CustomRegistrableDef {
    u16 regItem;
    ACTION_ID actionID; // 0xFF = don't set, 0xFE = ignore
    b32 retCode;

    FIELD_COMMON_EVENT fieldCommonEffectType;
    ShortcutMenuType subProcID;
    u32 subProcParam;
    b32 isCommonEvent;

    u32 txtLine; // From text/system/ShortcutMenu_CustomTxtDat
};

CustomRegistrableDef customRegistrableDefs[] = {
    #ifdef PHENOM_POKERADAR
    {
        .regItem  = REG_ITEM(36, 431),
        .actionID = 0xFE,
        .retCode  = true,

        .fieldCommonEffectType = FieldCommonEventTableMax + 431,
        .subProcID             = (ShortcutMenuType)0xFFFF,
        .subProcParam          = 0xFFFF,
        .isCommonEvent         = true,

        .txtLine = 0, // "[COLOR(2)]Poké Radar[COLOR(0)]" in text/system/768.txt
    },
    #endif
    { .regItem = 0xFFFF }, // Sentinel - don't remove!
};

extern "C" {
    #ifdef PW2CODE_EXPAND_ITEMS
    ItemType PW2Code_PML_ItemGetType(u16);
    #else
    ItemType PML_ItemGetType(u16);
    #endif

    ItemType PML_ItemGetType_Wrapper(u16 itemID) {
        for (CustomRegistrableDef* def = customRegistrableDefs; def->regItem != 0xFFFF; def++)
            if ((def->regItem & 0x3FF) == itemID)
                return ITEMTYPE_KEY;
        #ifdef PW2CODE_EXPAND_ITEMS
        return PW2Code_PML_ItemGetType(itemID);
        #else
        return PML_ItemGetType(itemID);
        #endif
    }
    ALIAS(THUMB_BRANCH_LINK_BagSave_GetPocketPtrByItem_0xa,    PML_ItemGetType_Wrapper);
    ALIAS(THUMB_BRANCH_LINK_BagSave_GetExistingItemPocket_0x8, PML_ItemGetType_Wrapper);
    ALIAS(THUMB_BRANCH_LINK_BagSave_GetActualItemPocket_0x12,  PML_ItemGetType_Wrapper);

    #if defined(PW2CODE_INFINITE_CANDY) || defined(PW2CODE_INFINITE_REPEL)
    REG_ID PW2Code_GetRegistrableID(ItemID);
    b32 PW2Code_ShortcutMenu_GetActionFromKeyItem(REG_ID, ACTION_ID*, b32*);
    b32 PW2Code_ShortcutMenu_SetKeyItemID(ShortcutMenuWork*, REG_ID);
    u32 PW2Code_PlayerActionPerms_IsActionBlocked(PlayerActionPerms*, ACTION_ID);
    #else
    REG_ID GetRegistrableID(ItemID);
    b32 ShortcutMenu_GetActionFromKeyItem(REG_ID, ACTION_ID*, b32*);
    b32 ShortcutMenu_SetKeyItemID(ShortcutMenuWork*, REG_ID);
    #endif

    REG_ID GetRegistrableID_Wrapper(ItemID itemID) {
        // If it is a custom registrable item, return our REG_ID
        for (CustomRegistrableDef* def = customRegistrableDefs; def->regItem != 0xFFFF; def++)
            if ((def->regItem & 0x3FF) == itemID)
                return def->regItem >> 10;
        #if defined(PW2CODE_INFINITE_CANDY) || defined(PW2CODE_INFINITE_REPEL)
        return PW2Code_GetRegistrableID(itemID);
        #else
        return GetRegistrableID(itemID);
        #endif
    }
    ALIAS(THUMB_BRANCH_LINK_Bag_IsItemRegistered_0x8, GetRegistrableID_Wrapper);
    ALIAS(THUMB_BRANCH_LINK_Bag_RegisterKeyItem_0x26,  GetRegistrableID_Wrapper);

    b32 ShortcutMenu_GetActionFromKeyItem_Wrapper(REG_ID registrableID, ACTION_ID* actionID, b32* isNotRegistrable) {
        // If it is a custom registrable item, use our action data
        for (CustomRegistrableDef* def = customRegistrableDefs; def->regItem != 0xFFFF; def++)
            if (def->regItem >> 10 == registrableID) {
                *isNotRegistrable = false;
                if (def->actionID != 0xFF) *actionID = def->actionID;
                return def->retCode;
            }
        #if defined(PW2CODE_INFINITE_CANDY) || defined(PW2CODE_INFINITE_REPEL)
        return PW2Code_ShortcutMenu_GetActionFromKeyItem(registrableID, actionID, isNotRegistrable);
        #else
        return ShortcutMenu_GetActionFromKeyItem(registrableID, actionID, isNotRegistrable);
        #endif
    }
    ALIAS(THUMB_BRANCH_LINK_EventShortcutChoicePopup_Callback_0x86, ShortcutMenu_GetActionFromKeyItem_Wrapper);
    ALIAS(THUMB_BRANCH_LINK_EventShortcutCallDirect_Callback_0x58,  ShortcutMenu_GetActionFromKeyItem_Wrapper);

    b32 ShortcutMenu_SetKeyItemID_Wrapper(ShortcutMenuWork* shortcutMenu, REG_ID registrableID) {
        // If it is a custom registrable item, use our key item data
        for (CustomRegistrableDef* def = customRegistrableDefs; def->regItem != 0xFFFF; def++)
            if (def->regItem >> 10 == registrableID) {
                if (def->fieldCommonEffectType != 0xFFFF) shortcutMenu->fieldCommonEffectType = def->fieldCommonEffectType;
                if (def->subProcID != 0xFFFF)             shortcutMenu->subProcID = def->subProcID;
                if (def->subProcParam != 0xFFFF)          shortcutMenu->subProcParam = def->subProcParam;
                return def->isCommonEvent;
            }
        #if defined(PW2CODE_INFINITE_CANDY) || defined(PW2CODE_INFINITE_REPEL)
        return PW2Code_ShortcutMenu_SetKeyItemID(shortcutMenu, registrableID);
        #else
        return ShortcutMenu_SetKeyItemID(shortcutMenu, registrableID);
        #endif
    }
    ALIAS(THUMB_BRANCH_LINK_EventShortcutChoicePopup_Callback_0x90, ShortcutMenu_SetKeyItemID_Wrapper);
    ALIAS(THUMB_BRANCH_LINK_EventShortcutCallDirect_Callback_0x4c,  ShortcutMenu_SetKeyItemID_Wrapper);

    int THUMB_BRANCH_LINK_BagDisp_DrawItemElement_0x1cc(ItemData* itemWork, ItemID itemID) {
        for (CustomRegistrableDef* def = customRegistrableDefs; def->regItem != 0xFFFF; def++)
            if ((def->regItem & 0x3FF) == itemID)
                return 1;
        return PML_ItemGetParam(itemWork, ITSTAT_FLAG2);
    }

    u32 THUMB_BRANCH_PlayerActionPerms_IsActionBlocked(PlayerActionPerms* perms, ACTION_ID actionID) {
        if (actionID == 0xFE) return 0;

        #if defined(PW2CODE_INFINITE_CANDY) || defined(PW2CODE_INFINITE_REPEL)
        return PW2Code_PlayerActionPerms_IsActionBlocked(perms, actionID);
        #else
        return perms->actionsBlocked[actionID];
        #endif
    }

    #ifdef CUSTOM_SHORTCUT_TXT
    void ListMenuCore_AppendMsgOption(void*, void*, u32, u32, HeapID);
    void THUMB_BRANCH_LINK_ShortcutView_FillList_0x34(void* listMenuWork, void* msgData, u32 msgIdx, u32 key, HeapID heapID) {
        if (key > ShortcutMenu_ItemMsg_Max)
            for (CustomRegistrableDef* def = customRegistrableDefs; def->regItem != 0xFFFF; def++)
                if (def->regItem >> 10 == key) {
                    msgData = GFL_MsgSysLoadData(0, 2, ShortcutMenu_CustomTxtDat, heapID);
                    ListMenuCore_AppendMsgOption(listMenuWork, msgData, def->txtLine, key, heapID);
                    GFL_MsgDataFree(msgData);
                    return;
                }
        ListMenuCore_AppendMsgOption(listMenuWork, msgData, msgIdx, key, heapID);
    }
    #endif
}
#endif
