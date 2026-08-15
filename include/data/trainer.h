#include "swantypes.h"

enum Gender: u8 {
    MALE,
    FEMALE,
};

struct TrainerCard {
    u16 string[]; // not varying size
    // ???
};

extern "C" Gender getTrainerGender(TrainerCard*);
