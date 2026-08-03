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
