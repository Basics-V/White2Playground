/*
    A big thank you to Paideieitor's PW2Code for reference
    and research on the Bag!
*/

#include "swantypes.h"
#include "system/game_data.h"
#include "Util.h"
#include "gfl/str/string.h"

struct Bag { // See Paideieitor/PW2Code/Headers/bag.h
    GameData* gameData;

    u8 unk1[4];
    void* trainerCardWork;

    u8 unk2[0x514];

    void* msgData;
    void* wordSetSystem;
    StrBuf* strBuf1;
    StrBuf* strBuf2;

    u8 unk3[0x370];
    
    u32 itemID;
    // ...
};

typedef void (Bag_StateFunc)(Bag*);

#ifdef CUSTOM_ITEM_USE
#include "save/savedata_bag.h"
#include "nds/gx.h"
#include "gfl/g2d/gfl_bg_sys.h"

extern "C" {
    b32 Bag_IsItemRepel(int);
    Bag_StateFunc Bag_WaitDialogue;
    void Bag_UpdateStateMachine(Bag*, Bag_StateFunc);
    void Bag_SetItemWindowState(Bag*);
    int PML_ItemGetParam(void*, u32);
    void GFL_MsgDataLoadStrbuf(void*, int, StrBuf*);
    void Bag_LoadItemName(Bag*, int, u32);
    void copyVarForText(void*, int, void*);
    void GFL_WordSetFormatStrbuf(void*, StrBuf*, StrBuf*);
    void Bag_CreateTextBox(Bag*, int);
    void Bag_DrawWindow(Bag*);
    void Bag_SetMenuBrightness(Bag*, b32);
    void GFL_SndSEPlay(u32);
    void Bag_SubItem(Bag*, u16);

    // General use message for using an item
    void FinishUse_Message(Bag* bag) { // References Bag_RepelEffect
        // Display messagebox
        GFL_MsgDataLoadStrbuf(bag->msgData, 0x3f, bag->strBuf1);
        copyVarForText(bag->wordSetSystem, 0, bag->trainerCardWork);
        Bag_LoadItemName(bag, 1, bag->itemID);
        GFL_WordSetFormatStrbuf(bag->wordSetSystem, bag->strBuf2, bag->strBuf1);
        Bag_CreateTextBox(bag, 1);

        // Wait for the player to close the messagebox
        Bag_UpdateStateMachine(bag, Bag_WaitDialogue);
    }

    // To skip the dialogue box that says you've used the item
    void FinishUse_Silent(Bag* bag) { // References Bag_WaitDialogue
        // Clear and redraw
        GFL_BGSysClearScr(G2D_BG3A);
        Bag_DrawWindow(bag);

        // Update view and control for player
        Bag_SetMenuBrightness(bag, true);
        Bag_SetItemWindowState(bag);
    }
}

typedef Bag_StateFunc CustomItemUseFunc;
struct CustomItemUseDef {
    u32 ID;
    CustomItemUseFunc* func;
};

extern "C" {
    void BlackFluteUse(Bag* bag) {
        Mi4::Printf("Black Flute has been used!\n");

        // Play a whistle sound effect
        GFL_SndSEPlay(1533); // 1757 could also work

        // Finish with a messagebox
        FinishUse_Message(bag);
    }
    void BigPearlUse(Bag* bag) {
        Mi4::Printf("Big Pearl has been used!\n");

        // Deplete item
        Bag_SubItem(bag, 1);

        // Finish silently and return to bag menu
        FinishUse_Silent(bag);
    }
}

// Define our custom functionality
CustomItemUseDef customItemUseDefs[] = {
    /*
    {
        68, // Black Flute
        &BlackFluteUse,
    },
    {
        89, // Big Pearl
        &BigPearlUse,
    },
    */
    { 0, NULL, }, // Sentinel
};

extern "C" {
    // Redirect use function to the repel function
    u8 THUMB_BRANCH_Bag_CanUse(int itemID) {
        // Vanilla
        if (Bag_IsItemRepel(itemID)) return 1;
        if ((itemID + 0xFD98) & 0xFFFF < 2) return 2;

        // Check for custom item use
        for (CustomItemUseDef* def = customItemUseDefs; def->func != NULL; def++)
            if (def->ID == itemID)
                return 1;

        // If none applicable
        return 0;
    }

    // Execute custom code if the "repel" is our custom item
    b32 THUMB_BRANCH_LINK_Bag_RepelEffect_0xe(int itemID, Bag* bag) {
        itemID &= 0xFFFF; // Replaced code... itemID is a u16

        // Check if we're executing a custom use item
        for (CustomItemUseDef* def = customItemUseDefs; def->func != NULL; def++) {
            if (def->ID == itemID) {
                // Execute the CustomItemUseFunc
                def->func(bag);

                // Finish and don't run the rest of the repel function
                return false;
            }
        }
        return Bag_IsItemRepel(itemID);
    }

    // Show the "use" button
    int THUMB_BRANCH_LINK_Bag_GetUseButtonType_0xc(void* itemWork, u32 itemField, BagItem* bagItem) {
        // Check if it's a custom item use
        for (CustomItemUseDef* def = customItemUseDefs; def->func != NULL; def++)
            if (def->ID == bagItem->ItemID)
                return 1; // != 0

        // Otherwise, treat as normal
        return PML_ItemGetParam(itemWork, itemField);
    }
}
#endif
