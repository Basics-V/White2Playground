#pragma once
#include "field/fieldmap.h"

struct PhenomRadarEvent {
    Field* field;
    u8 flags;
};

#ifdef PHENOM_POKERADAR
#define PHPKRDR_EVTWK 16404

#define PHPKRDR_SCRDAT    1800
#define PHPKRDR_SCRID_MIN 20800
#define PHPKRDR_SCRID_MAX 20802
#define PHPKRDR_TXTDAT    800

#define PHPKRDR_SCR_useFailed  20800
#define PHPKRDR_SCR_spawnFail  20801
#define PHPKRDR_SCR_useSuccess 20802

#define PHPKRDR_FLDEFF_MAIN 284
#endif
