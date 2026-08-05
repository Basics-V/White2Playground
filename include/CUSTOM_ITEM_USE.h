#pragma once
#include "swantypes.h"
#include "MODS.h"

#ifdef CUSTOM_ITEM_USE
#include "Bag.h"
#include "save/savedata_bag.h"
#include "nds/gx.h"
#include "gfl/g2d/gfl_bg_sys.h"

typedef Bag_StateFunc CustomItemUseFunc;
typedef GameEvent* (CustomItemActiveFunc)(Field*, GameSystem*);
struct CustomItemUseDef {
    u32 ID;
    CustomItemUseFunc* func;
    CustomItemActiveFunc* activate;
};

// Define our custom functionality
extern CustomItemUseDef customItemUseDefs[];
#endif
