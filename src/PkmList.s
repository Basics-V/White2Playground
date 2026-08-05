.thumb
#include "MODS.h"

#ifdef HIDE_HM
#ifdef HIDE_DIG
@ Return 0 for move dig in list
FULL_COPY_PkmList_MoveMatchHM_0x80:
    MOV R0,#0x0
    .size FULL_COPY_PkmList_MoveMatchHM_0x80, . - FULL_COPY_PkmList_MoveMatchHM_0x80
#endif

#ifdef HIDE_TELEPORT
@ Return 0 for move teleport in list
FULL_COPY_PkmList_MoveMatchHM_0x7c:
    MOV R0,#0x0
    .size FULL_COPY_PkmList_MoveMatchHM_0x7c, . - FULL_COPY_PkmList_MoveMatchHM_0x7c
#endif
#endif
