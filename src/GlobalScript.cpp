/*
    Handles the injection of our new global script file(s).

    A huge thanks to Hello007, PlatinumMaster, and everyone else
    who worked on gscr_loader.c and scr_plgext_loader.c for their
    pioneering in this incredible feat!
*/
#include "MODS.h"
#include "swantypes.h"
#include "GlobalScript.h"
#include "Util.h"

#ifdef CUSTOM_SCRIPT
#include "CUSTOM_SCRIPT.h"
#include "data/arcid_def.h"
#include "gfl/core/gfl_heap.h"
#include "gfl/fs/gfl_archive.h"
#include "FileHandler.h"
extern "C" {
    // Allow our scripts to be called from the field
    b32 THUMB_BRANCH_FieldScript_CheckSCRID(u16 scriptID) {
        if (scriptID == 2000) return false;
        if (scriptID < GLOBAL_SCRIPT_TABLE[0].endID) return true;
        
        // Check if the script ID is one of ours from the customScriptTable
        for (CustomScriptEntry* scr = customScriptTable; scr->name != NULL; scr++)
            if (scr->global.startID <= scriptID && scriptID <= scr->global.endID)
                return true;

        return false;
    }

    // Match our script IDs to our script file and text file
    u16 THUMB_BRANCH_LINK_FieldScript_CreateVM_0x82(u16 zoneID, u16 scriptID, u16* scrDatID, u16* textArcID, u16* textDatID) {
        // If it's one of our scripts...
        for (CustomScriptEntry* scr = customScriptTable; scr->name != NULL; scr++) {
            if (scr->global.startID <= scriptID && scriptID <= scr->global.endID) {
                // Then identify our script data ID and its corresponding text archive IDs
                *scrDatID  = scr->global.scrDatID;
                *textArcID = scr->global.textArcID; // The events text arc
                *textDatID = scr->global.textDatID; // Our text file!

                // Get relative script ID
                return scriptID - scr->global.startID;
            }
        }

        // Otherwise, resolve a normal script ID
        return FieldScript_ResolveSCRID(zoneID, scriptID, scrDatID, textArcID, textDatID);
    }

    // Inject our custom script file if it is requested
    u8* THUMB_BRANCH_FieldScript_LoadData(u16 scrDatID, HeapID heapID) {
        for (CustomScriptEntry* scr = customScriptTable; scr->name != NULL; scr++) {
            if (scr->global.scrDatID == scrDatID) {
                // Handle loading our custom script file
                u32 fileSize = GetFileSize(scr->name);
                u8* buffer = (u8*)GFL_HeapAllocate(heapID, fileSize, 0, __FILE__, __LINE__);
                if (ReadDataFromFile(scr->name, fileSize, buffer, 0)) {
                    // If the read succeeds, return our custom buffer
                    return buffer;
                } else {
                    // If the read fails, free the buffer
                    GFL_HeapFree(buffer);
                }
            }
        }
        return (u8*)GFL_ArcSysReadHeapNewLZ(ARCID_EVENT_SCRIPT, scrDatID, 0, heapID);
    }
}
#endif
