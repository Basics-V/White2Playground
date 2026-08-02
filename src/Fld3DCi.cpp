/*
    A more complete implementation is planned.
    For now, enjoy a hacky work-around for PHENOM_POKERADAR!
*/
#include "swantypes.h"

struct Fld3DCi_Meta {
    u8 unk1[8];

    u16 bmd0Ind[2];

    u8 unk2[4];

    u16 bta0Ind1[4];
    u16 bta0Ind2[4];

    u8 unk3[4];
};

#ifdef PHENOM_POKERADAR
#include "PHENOM_POKERADAR.h"
#include "Util.h"
#include "gfl/fs/gfl_archive.h"
#include "field/field_eventwork.h"
extern "C" {
    void THUMB_BRANCH_LINK_Fld3DCi_LoadG3DSceneTemplate_0x12(Fld3DCi_Meta* cutInMeta, int arcID, u16 datID) {
        GFL_ArcSysRead(cutInMeta, arcID, datID);

        if (*EventWork_GetWkPtr(Mi4::GameSys()->m_GameData->m_EventWork, PHPKRDR_EVTWK) == 5)
            cutInMeta->bmd0Ind[1] = PHPKRDR_FLDEFF_MAIN;
    }
}
#endif
