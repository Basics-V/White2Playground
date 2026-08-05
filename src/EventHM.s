.thumb
#include "MODS.h"

#ifdef BLOCK_HM
@ Disable use of dig
FULL_COPY_EventDigCall_Callback_0x3a:
    MOV R0,#0x1
    ADD SP,#0x4
    POP {R3,R4,R5,R6,PC}
    .size FULL_COPY_EventDigCall_Callback_0x3a, . - FULL_COPY_EventDigCall_Callback_0x3a
FULL_COPY_EventDigCall_Callback_0x50:
    .word BLOCKHM_SCR_fail
    .size FULL_COPY_EventDigCall_Callback_0x50, . - FULL_COPY_EventDigCall_Callback_0x50

@ Disable use of teleport
FULL_COPY_EventTeleportCall_Callback_0x3a:
    MOV R0,#0x1
    ADD SP,#0x4
    POP {R3,R4,R5,R6,PC}
    .size FULL_COPY_EventTeleportCall_Callback_0x3a, . - FULL_COPY_EventTeleportCall_Callback_0x3a
FULL_COPY_EventTeleportCall_Callback_0x50:
    .word BLOCKHM_SCR_fail
    .size FULL_COPY_EventTeleportCall_Callback_0x50, . - FULL_COPY_EventTeleportCall_Callback_0x50
#endif
