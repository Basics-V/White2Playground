#pragma once
#include "GlobalScript.h"

struct CustomScriptEntry {
    ScriptGlobalTableEntry global;
    const char* name;
};

#ifdef PHENOM_POKERADAR
#include "PHENOM_POKERADAR.h"
#endif

CustomScriptEntry customScriptTable[] = {
    #ifdef PHENOM_POKERADAR
    {
        .global = {
            .startID   = PHPKRDR_SCRID_MIN,
            .endID     = PHPKRDR_SCRID_MAX,
            .scrDatID  = PHPKRDR_SCRDAT,
            .textArcID = 3,
            .textDatID = 800,
        },
        .name = "White2Playground/PHENOM_POKERADAR.ev",
    },
    #endif
    { .name = NULL, }, // Sentinel - don't remove!
};
