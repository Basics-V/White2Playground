#include "MODS.h"

#include "swantypes.h"

#ifdef NO_SEASON_BANNER

STRUCT_DECLARE(SeasonBanner);
struct SeasonBanner {
    u8 unk1[0x14];
    u8 finalSeason;
    u8 currentSeason;
};

void EventSeasonBanner_ProcessState(SeasonBanner*, u32*, u32);
void EventSeasonBanner_SetCancelled(SeasonBanner*);
void EventSeasonBanner_End(SeasonBanner*);

// Self-explanatory
u32 THUMB_BRANCH_EventSeasonBanner_GetFadeInTime(SeasonBanner*)  { return 0; }
u32 THUMB_BRANCH_EventSeasonBanner_GetStayTime(SeasonBanner*)    { return 0; }
u32 THUMB_BRANCH_EventSeasonBanner_GetFadeOutTime(SeasonBanner*) { return 0; }

// Comment out for a seizure
void THUMB_BRANCH_LINK_EventSeasonBanner_CreateFieldTransition_0x58(SeasonBanner* seaBan, u32* state, u32 nextState) {
    EventSeasonBanner_ProcessState(seaBan, state, 0);
    EventSeasonBanner_ProcessState(seaBan, state, 1);
    EventSeasonBanner_ProcessState(seaBan, state, 2);
    EventSeasonBanner_ProcessState(seaBan, state, 3);
    seaBan->currentSeason = seaBan->finalSeason;
    EventSeasonBanner_ProcessState(seaBan, state, 4);
}

#endif
