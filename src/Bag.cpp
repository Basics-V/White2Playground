/*
    A big thank you to Paideieitor's PW2Code for reference
    and research on the Bag!
*/
#include "MODS.h"
#include "swantypes.h"

#include "Util.h"
#include "Bag.h"

#ifdef CUSTOM_ITEM_USE
#include "CUSTOM_ITEM_USE.h"
#ifdef PHENOM_POKERADAR
#include "data/heapid_def.h"
#include "system/game_event.h"
#include "nds/mem.h"
#include "field/fieldmap.h"
#include "field/field_encount.h"
#include "field/field_encount_data.h"
#include "field/field_effect_encount_state.h"
#include "field/field_3dci.h"

struct PhenomRadarEvent {
    Field* field;
    u8 flags;
};
#endif

extern "C" {
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

    // Execute an action
    void FinishUse_ExecAction(Bag* bag, BagActionID action) {
        bag->nextActionID = action;
        Bag_UpdateStateMachine(bag, NULL);
    }
}

extern "C" {
    #ifdef PHENOM_POKERADAR
    b32 EncSys_IsActive(EncountSystem*, u32);
    void* getTrainerCardDataBlkAddress(GameData*);
    bool isBadgeObtained(void*, u32);
    u32 Field_GetResolvedControllerTypeID(Field*);
    void positionShakingSpot(EncountSystem*, EffectEncountState*, u8);
    void SpawnPhenomenon(EncountSystem*, EffectEncountState*);
    void EncountSystem_CancelPhenomenon(EncountSystem*);
    void EncountSystem_CancelPhenomenonCore(EncountSystem*, void*);
    EncountSystem* Field_GetEncountSystem(Field*);
    EncountState* GameData_GetEncountState(GameData*);
    Fld3DCi* Field_Get3DCi(Field*);
    GameEvent* EventFieldEffect_Create(GameSystem*, Fld3DCi*, u32);

    void PokeRadarUse(Bag* bag) {
        Mi4::Printf("Poké Radar has been used!\n");

        // Close the bag to prepare for our FieldAction
        FinishUse_ExecAction(bag, BAG_CUSTOM);
    }

    GameEventReturnCode PhenomRadarCallback(GameEvent* event, u32* state, void* evDat) {
        PhenomRadarEvent* eventData = (PhenomRadarEvent*)evDat;

        // Fetch necessary works...
        EncountSystem* encSys = Field_GetEncountSystem(eventData->field);
        EncountState* encState = GameData_GetEncountState(encSys->m_GameData);
        EncData* encData = encSys->m_EncData;
        EffectEncountState* effEncState = (EffectEncountState*)encSys->m_EffectEncountState;

        /* Heavily references UpdatePhenomenon/OVL_36:0x21A20AD */
        switch (*state) {
            case 0: {
                if (
                    EncSys_IsActive(encSys, 2) &&
                    isBadgeObtained(getTrainerCardDataBlkAddress(encSys->m_GameData), 0) &&
                    Field_GetResolvedControllerTypeID(encSys->m_Field) == 0
                ) {
                    eventData->flags = encData->UserData[2] != 0;
                    if (encData->UserData[4] || encData->UserData[6])
                        eventData->flags |= 2;
                    if (eventData->flags != 0) {
                        // If a phenomenon already exists
                        if ((encState->field_24 & 0xF00) != 0) {
                            EncountSystem_CancelPhenomenonCore(encSys, encSys->m_EffectEncountState);
                        }

                        // Spawn the phenomenon
                        positionShakingSpot(encSys, effEncState, eventData->flags);
                        if (effEncState->maxMapEffects != 0) {
                            /*
                            Fld3DCi* fld3dci = Field_Get3DCi(eventData->field);
                            GameEvent* fieldEffectEvent = EventFieldEffect_Create(GameEvent_GetGameSystem(event), fld3dci, 76);
                            GameEvent_ChainNext(event, fieldEffectEvent);
                            */
                            (*state)++;
                            break;
                        } else {
                            // Failed to find a spot!
                            EventScriptCall_Start(event, PHPKRDR_SCR_spawnFail, NULL, NULL, HEAPID_FIELDMAP);
                            *state = 3;
                            break;
                        }
                    }
                }
                // Failed to use the item!
                EventScriptCall_Start(event, PHPKRDR_SCR_useFailed, NULL, NULL, HEAPID_FIELDMAP);
                *state = 3;
                break;
            }
            case 1:
                // Succeeded to use the item!
                EventScriptCall_Start(event, PHPKRDR_SCR_useSuccess, NULL, NULL, HEAPID_FIELDMAP);
                (*state)++;
                break;
            case 2:
                while ((encState->field_24 & 0xF00) == 0) SpawnPhenomenon(encSys, effEncState);
            case 3:
                return GAMEEVENT_DONE;
        }
        return GAMEEVENT_CONTINUE;
    }

    GameEvent* PokeRadarActivate(Field* field, GameSystem* gameSys) {
        // Setup Phenomenon Poké Radar Event
        GameEvent* event = GameEvent_Create(gameSys, NULL, PhenomRadarCallback, sizeof(PhenomRadarEvent));
        PhenomRadarEvent* eventData = (PhenomRadarEvent*)GameEvent_GetData(event);
        sys_memset(eventData, 0, sizeof(PhenomRadarEvent));
        eventData->field = field;
        return event;
    }
    #endif
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

CustomItemUseDef customItemUseDefs[] = {
    #ifdef PHENOM_POKERADAR
    {
        431, // Poké Radar
        &PokeRadarUse,
        &PokeRadarActivate,
    },
    #endif
    /*
    {
        68, // Black Flute
        &BlackFluteUse,
        NULL,
    },
    {
        89, // Big Pearl
        &BigPearlUse,
        NULL,
    },
    */
    { 0, NULL, NULL, }, // Sentinel - don't remove!
};

extern "C" {
    // Redirect use function to the repel function
    u8 THUMB_BRANCH_Bag_CanUse(int itemID) {
        // Vanilla
        if (Bag_IsItemRepel(itemID)) return 1;
        if (itemID == 616 || itemID == 617) return 2; // 616 & 617, Light/Dark Stones

        // Check for custom item use
        for (CustomItemUseDef* def = customItemUseDefs; def->func != NULL; def++)
            if (def->ID == itemID)
                return 1;

        // If none applicable
        return 0;
    }

    #ifdef PW2CODE_INFINITE_REPEL
    u32 PW2Code_Bag_RepelEffect(Bag*);
    #endif

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
        #ifdef PW2CODE_INFINITE_REPEL
        PW2Code_Bag_RepelEffect(bag);
        return false;
        #endif
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
