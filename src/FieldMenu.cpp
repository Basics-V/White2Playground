#include "Util.h"
#include "swantypes.h"

enum FieldMenuButton: u32 {
    EOS          = 0x0,
    BLANK        = 0x7,
    POKEMON      = 0x1,
    POKEDEX      = 0x2,
    BAG          = 0x3,
    TRAINER_CARD = 0x4,
    #ifndef NO_SAVE
    SAVE         = 0x5,
    #else
    SAVE         = BLANK,
    #endif
    OPTIONS      = 0x6,
    RETIRE       = 0x8,
};

struct FieldMenuButtonEntry { /* 1 = Pokemon, 2 = PokeDex, 3 = Bag, 4 = Trainer Card, 5 = Save, 6 = Options, 7 = Blank, 8 = Retire, 0 = EOS */
    FieldMenuButton button0;
    FieldMenuButton button1;
    FieldMenuButton button2;
    FieldMenuButton button3;
    FieldMenuButton button4;
    FieldMenuButton button5;
    FieldMenuButton EOS; /* Always 0 */
};

// Overwrite the existing FieldMenuButtonArray... no changes are made here
FieldMenuButtonEntry FULL_COPY_FieldMenuButtonArray[] = {
    {
        POKEMON,
        POKEDEX,
        BAG,
        TRAINER_CARD,
        SAVE,
        OPTIONS,
        EOS,
    },
    {
        POKEMON,
        POKEDEX,
        BAG,
        TRAINER_CARD,
        OPTIONS,
        BLANK,
        EOS,
    },
    {
        POKEMON,
        BAG,
        TRAINER_CARD,
        SAVE,
        OPTIONS,
        BLANK,
        EOS,
    },
    {
        BAG,
        TRAINER_CARD,
        SAVE,
        OPTIONS,
        BLANK,
        BLANK,
        EOS,
    },
    {
        POKEMON,
        POKEDEX,
        BAG,
        TRAINER_CARD,
        OPTIONS,
        BLANK,
        EOS,
    },
    {
        POKEMON,
        POKEDEX,
        BAG,
        TRAINER_CARD,
        OPTIONS,
        BLANK,
        EOS,
    },
    {
        POKEMON,
        POKEDEX,
        TRAINER_CARD,
        SAVE,
        OPTIONS,
        RETIRE,
        EOS,
    },
};

#ifdef NO_SAVE
// Only count the number of buttons that are bounded by non-FieldMenuButton.BLANK
extern "C" u8 THUMB_BRANCH_FieldMenu_CountActiveButtons(u8 buttonEntry) {
    u32* entryButton = (u32*)&FULL_COPY_FieldMenuButtonArray[buttonEntry];
    int valid = 0;
    for (int i = 0; entryButton[i] != EOS; i++) {
        if (entryButton[i] == BLANK) {
            for (int j = i + 1; entryButton[j] != EOS; j++) {
                if (entryButton[j] != BLANK) {
                    valid++; break;
                }
            }
            continue;
        }
        valid++;
    }
    return valid;
}
#endif
