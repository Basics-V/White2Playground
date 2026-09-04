#include "swantypes.h"
#include "system/game_data.h"

ENUM_DECLARE_EX(EncType, u32)
enum EncType: u32 {
    WILD       = 0x0,
    PHENOMENON = 0x1,
    // ...
};

STRUCT_DECLARE(EncountManager)
struct EncountManager {
    GameData* gameData;

    u8 unk1[8];

    EncType encountType;
    // ...
};
