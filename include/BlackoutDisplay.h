#pragma once
#include "system/gamesystem.h"
#include "gfl/core/gfl_procsys.h"
#include "data/trainer.h"

#define BLACKOUT_DISPLAY_OVL_ID 0x127
static GameProcFunctions* BLACKOUT_DISPLAY_PROC_LIST;

struct BlackoutInitProcData {
    GameSystem* gameSys;
    b32 respawnPokeCen;
    TrainerCard* trainerCard;
};

extern "C" {
    b32 BlackoutDisplayProc_Init(GameProc*, u32*, void*, void*);
    b32 BlackoutDisplayProc_Update(GameProc*, u32*, void*, void*);
    b32 BlackoutDisplayProc_End(GameProc*, u32*, void*, void*);
}
