.thumb
#include "MODS.h"

#ifdef FISHING_NO_WAIT
FULL_COPY_EventFieldFishing_Callback_0xa4:
    MOV R0,#0x2
    NOP
    .size FULL_COPY_EventFieldFishing_Callback_0xa4, . - FULL_COPY_EventFieldFishing_Callback_0xa4
#elif defined FISHING_CONVENIENT
FULL_COPY_EventFieldFishing_Callback_0x96:
    MOV R0,#0x0
    NOP
    .size FULL_COPY_EventFieldFishing_Callback_0x96, . - FULL_COPY_EventFieldFishing_Callback_0x96
FULL_COPY_EventFieldFishing_Callback_0x118:
    MOV R0,R4
    MOV R1,R6
    NOP
    NOP
    .size FULL_COPY_EventFieldFishing_Callback_0x118, . - FULL_COPY_EventFieldFishing_Callback_0x118
FULL_COPY_EventFieldFishing_Callback_0x124:
    NOP
    .size FULL_COPY_EventFieldFishing_Callback_0x124, . - FULL_COPY_EventFieldFishing_Callback_0x124
#endif
