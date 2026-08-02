#include "swantypes.h"
#include "system/game_data.h"

enum EncType: u32 {
    WILD       = 0x0,
    PHENOMENON = 0x1,
    // ...
};

struct EncountManager {
    GameData* gameData;

    u8 unk1[8];

    EncType encountType;
    // ...
};

#ifdef PHENOM_SHINY_TWEAK
#include "PHENOM_SHINY_TWEAK.h"
#include "Util.h"
extern "C" {
    int PassPower_ApplyLuckyShiny(u16);
    int THUMB_BRANCH_LINK_FieldEncount_CreateWildPkm_0x32(u16 rerolls, EncountManager* encMgr, b32 shinyCharm) {
        if (shinyCharm) rerolls += 2;

        // If it's a phenomenon encounter...
        if (encMgr->encountType == PHENOMENON)
            rerolls += PHENOM_SHINY_REROLL;

        return PassPower_ApplyLuckyShiny(rerolls);
    }
}
#endif
