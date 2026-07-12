/*
    Example usage (in PokéScript):

    public static void main_??() {
        // Example vars
        int npcId = Player.GetFacingActorID(); int x; int z;
        Actor.GetGPos(npcId, x, z);
        z += 5;

        // Set our event work to activate special functionality
        EventWorks.Set(0x4195, npcId); // Must match BALLTOSS_NPC_VAR

        // Call the throw out animation
        Base.CMD_20E(0, x, 0, z, 3, 8);
        Base.CMD_20F(0, x, 0, z);
        Base.CMD_211(0);

        // Reset to allow vanilla scripts to work
        EventWorks.Set(0x4195, 255); // Must match BALLTOSS_NPC_VAR

        Runtime.FinishSubEvents();
        Actor.UnpauseAll();
    }

    If you want to throw from the player, use npcId 255.
    If you use BALLTOSS_ORIGIN_MAN, you MUST default set *BALLTOSS_NPC_VAR = 255 to maintain vanilla script functionality
    See the script command documentation below for more information:
    https://docs.google.com/spreadsheets/d/1zvLQFVdv6kbEgP9TY9yfV6ChK0qsz79E6PvF5lohnGk/edit?gid=0#gid=0&range=B481
*/

#include "swantypes.h"
#include "Util.h"
#define BALLTOSS_NPC_VAR 0x4195 // Eventwork, *X = npcId

#ifdef BALLTOSS_ORIGIN_MAN
#include "math/vector.h"
#include "system/gamesystem.h"
#include "field/field_player.h"
extern "C" {
    u16* EventWork_GetWkPtr(EventWorkSave*, int);
    FieldActor* FindFieldActor(FieldActorSystem*, u16);
    VecFx32* GetMModelWPosPtr(FieldActor*);

    // Force grab custom NPC pos instead of FieldPlayer pos
    void THUMB_BRANCH_LINK_s020e_PlayPokeballToss_0x64(FieldPlayer* fieldPlayer, VecFx32* destPos) {
        GameData* gameData = fieldPlayer->m_Field->m_GameData;
        EventWorkSave* eventWork = gameData->m_EventWork;

        // Fetch our target NPC's ID from our BALLTOSS_NPC_VAR
        u16 npcID = *EventWork_GetWkPtr(eventWork, BALLTOSS_NPC_VAR); // 255 is the player

        FieldActor* npcOrigin = FindFieldActor(gameData->m_ActorSystem, npcID);
        *destPos = *GetMModelWPosPtr(npcOrigin);
    }
}
#endif
