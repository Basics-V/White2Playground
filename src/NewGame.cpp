#include "Util.h"
#include "swantypes.h"

enum Gender: u8 {
    MALE,
    FEMALE,
};

struct StrBuf {
    u16 field_0x0;
    u16 bufLen;
    u16 field_0x4[2];
    wchar_t charBuf;
    // ???
};

#define INTRO_NAME   L"BasicsV" // Max is 7 characters
#define INTRO_GENDER MALE

#ifdef SKIP_INTRO_DIALOGUE
extern "C" {
    void NewGame_CreateTrainerCard(void*, StrBuf*, Gender);

    // Force set our specified/set name and gender
    void THUMB_BRANCH_LINK_NewGame_Main_0x8e(void* trainerCardWork, StrBuf* strBuf, Gender gender) {
        // Store INTRO_NAME in the StrBuf
        wchar_t* charBuf = &strBuf->charBuf;
        int i;
        for (i = 0; INTRO_NAME[i] != L'\0'; i++)
            charBuf[i] = INTRO_NAME[i];
        charBuf[i] = -1;
        strBuf->bufLen = i;

        // Create the trainer card
        NewGame_CreateTrainerCard(trainerCardWork, strBuf, INTRO_GENDER);
    }
}
#endif
