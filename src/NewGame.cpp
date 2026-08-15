#include "MODS.h"
#include "Util.h"
#include "swantypes.h"
#include "gfl/str/string.h"
#include "data/trainer.h"

#define INTRO_NAME   L"BasicsV" // Max is 7 characters
#define INTRO_GENDER MALE

#ifdef SKIP_INTRO_DIALOGUE
extern "C" {
    void NewGame_CreateTrainerCard(TrainerCard*, StrBuf*, Gender);

    // Force set our specified/set name and gender
    void THUMB_BRANCH_LINK_NewGame_Main_0x8e(TrainerCard* trainerCardWork, StrBuf* strBuf, Gender gender) {
        // Store INTRO_NAME in the StrBuf
        u16* string = strBuf->string;
        int i;
        for (i = 0; INTRO_NAME[i] != L'\0'; i++)
            string[i] = INTRO_NAME[i];
        string[i] = -1;
        strBuf->charCount = i;

        // Create the trainer card
        NewGame_CreateTrainerCard(trainerCardWork, strBuf, INTRO_GENDER);
    }
}
#endif
