.thumb
#include "MODS.h"

#ifdef PERMADEATH
FULL_COPY_ServerFlow_UseItemRevive_0xa:
    MOV R0,#0x0
    NOP
    .size FULL_COPY_ServerFlow_UseItemRevive_0xa, . - FULL_COPY_ServerFlow_UseItemRevive_0xa
#endif

#ifdef FIRST_ENCOUNTER
FULL_COPY_ServerCommand_TrainerBlockBall_0x4a:
    MOV R0,R5
    .size FULL_COPY_ServerCommand_TrainerBlockBall_0x4a, . - FULL_COPY_ServerCommand_TrainerBlockBall_0x4a
#endif
