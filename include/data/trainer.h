#include "swantypes.h"

ENUM_DECLARE_EX(Gender, u8)
enum Gender: u8 {
    MALE,
    FEMALE,
};

STRUCT_DECLARE(TrainerCard)
struct TrainerCard {
    u16 string[]; // not varying size
    // ???
};

C_DECL_BEGIN
Gender getTrainerGender(TrainerCard*);
C_DECL_END
