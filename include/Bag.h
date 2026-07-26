#pragma once
#include "swantypes.h"
#include "system/game_data.h"
#include "gfl/str/string.h"

enum BagActionID: u32 {   // Extended use denoted w/ in-line comments
    BAG_CLOSE      = 0x0, // 0x1
    BAG_GIVE       = 0x2, // 0x3, 0x4, 0x9
    BAG_POKEUSE    = 0x5, // 0xC
    BAG_TM_TEACH   = 0x6,
    BAG_MAP        = 0x7,
    BAG_PALPAD     = 0x8,
    BAG_BICYCLE    = 0xA, // 0xB
    BAG_ENTRALINK  = 0xD,
    BAG_ESCAPE     = 0xE,
    BAG_SWEET      = 0xF,
    BAG_FISHROD    = 0x10,
    BAG_VSRECORD   = 0x11,
    BAG_GIVEMAIL   = 0x12,
    BAG_READMAIL   = 0x13,
    BAG_DOWSE      = 0x14,
    BAG_XTRANS     = 0x15,
    BAG_MEDALBOX   = 0x16,
    // ...after this, BAG_GIVE repeats
    #ifdef CUSTOM_ITEM_USE
    BAG_CUSTOM     = 0x17,
    #endif
};

struct Bag { // See Paideieitor/PW2Code/Headers/bag.h
    GameData* gameData;

    u8 unk1[4];
    void* trainerCardWork;

    u8 unk2[0x514];

    void* msgData;
    void* wordSetSystem;
    StrBuf* strBuf1;
    StrBuf* strBuf2;

    u8 unk3[0x368];

    BagActionID nextActionID;
    u32 bagItemActions;
    u32 itemID;

    u8 unk4[0x16B0];
};

typedef void (Bag_StateFunc)(Bag*);

extern "C" {
    b32 Bag_IsItemRepel(int);
    Bag_StateFunc Bag_WaitDialogue;
    void Bag_UpdateStateMachine(Bag*, Bag_StateFunc);
    void Bag_SetItemWindowState(Bag*);
    int PML_ItemGetParam(void*, u32);
    void Bag_LoadItemName(Bag*, int, u32);
    void Bag_CreateTextBox(Bag*, int);
    void Bag_DrawWindow(Bag*);
    void Bag_SetMenuBrightness(Bag*, b32);
    void Bag_SubItem(Bag*, u16);
}
