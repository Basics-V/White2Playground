#pragma once
#include "GlobalScript.h"
#include "MODS.h"

#ifdef CUSTOM_SCRIPT
struct CustomScriptEntry {
    ScriptGlobalTableEntry global;
    const char* name;
};

CustomScriptEntry customScriptTable[] = {
    #ifdef PHENOM_POKERADAR
    {
        .global = {
            .startID   = PHPKRDR_SCRID_MIN,
            .endID     = PHPKRDR_SCRID_MAX,
            .scrDatID  = PHPKRDR_SCRDAT,
            .textArcID = 3,
            .textDatID = PHPKRDR_TXTDAT,
        },
        .name = "White2Playground/PHENOM_POKERADAR.ev",
    },
    #endif
    #ifdef BLOCK_HM
    {
        .global = {
            .startID   = BLOCKHM_SCRID_MIN,
            .endID     = BLOCKHM_SCRID_MAX,
            .scrDatID  = BLOCKHM_SCRDAT,
            .textArcID = 3,
            .textDatID = BLOCKHM_TXTDAT,
        },
        .name = "White2Playground/BLOCK_HM.ev",
    },
    #endif
    { .name = NULL, }, // Sentinel - don't remove!
};
#endif
