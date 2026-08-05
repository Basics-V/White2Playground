.thumb
#include "MODS.h"

#ifdef PHENOM_RAND_MAN
@ Load GameData* into R1 for IncPhenomenonStepCount
FULL_COPY_UpdatePhenomenon_0xb6:
    LDR R1,[R5,#0x8]
    .size FULL_COPY_UpdatePhenomenon_0xb6, . - FULL_COPY_UpdatePhenomenon_0xb6

@ Load GameSystem* into R0 for random calculation
FULL_COPY_UpdatePhenomenon_0xc2:
    LDR R0,[R5,#0x4]
    .size FULL_COPY_UpdatePhenomenon_0xc2, . - FULL_COPY_UpdatePhenomenon_0xc2

@ Load GameSystem* into R0 for random calculation
FULL_COPY_UpdatePhenomenon_0xcc:
    LDR R0,[R5,#0x4]
    .size FULL_COPY_UpdatePhenomenon_0xcc, . - FULL_COPY_UpdatePhenomenon_0xcc

@ Don't multiply the cap by 0xA
FULL_COPY_UpdatePhenomenon_0xd4:
    MOV R1,R4
    CMP R1,R0
    .size FULL_COPY_UpdatePhenomenon_0xd4, . - FULL_COPY_UpdatePhenomenon_0xd4
#endif

#ifdef PHENOM_NO_ENCOUNT
@ Overwrite encounter branch instructions
FULL_COPY_CreateRandomPhenomenonEvent_0x7c:
    NOP
    .size FULL_COPY_CreateRandomPhenomenonEvent_0x7c, . - FULL_COPY_CreateRandomPhenomenonEvent_0x7c
FULL_COPY_CreateRandomPhenomenonEvent_0xa6:
    NOP
    .size FULL_COPY_CreateRandomPhenomenonEvent_0xa6, . - FULL_COPY_CreateRandomPhenomenonEvent_0xa6
#elif defined PHENOM_ONLY_ENCOUNT
@ Overwrite encounter branch instructions
FULL_COPY_CreateRandomPhenomenonEvent_0x7a:
    NOP
    .size FULL_COPY_CreateRandomPhenomenonEvent_0x7a, . - FULL_COPY_CreateRandomPhenomenonEvent_0x7a
FULL_COPY_CreateRandomPhenomenonEvent_0xa4:
    NOP
    .size FULL_COPY_CreateRandomPhenomenonEvent_0xa4, . - FULL_COPY_CreateRandomPhenomenonEvent_0xa4
#endif
