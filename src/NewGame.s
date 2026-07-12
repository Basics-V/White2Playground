.thumb

#ifdef SKIP_INTRO_DIALOGUE
@ Always skip to trainer card registration
FULL_COPY_NewGame_Main_0x12:
    MOV R1,#0x4
    .size FULL_COPY_NewGame_Main_0x12, . - FULL_COPY_NewGame_Main_0x12

@ Return after trainer card registration
FULL_COPY_NewGame_Main_0xa4:
    MOV R0,#0x1
    POP {R3,R4,R5,R6,R7,PC}
    .size FULL_COPY_NewGame_Main_0xa4, . - FULL_COPY_NewGame_Main_0xa4
#endif
