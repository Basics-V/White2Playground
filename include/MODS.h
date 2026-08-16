#pragma once

#ifdef PHENOM_POKERADAR
    #ifndef CUSTOM_ITEM_USE
        #define CUSTOM_ITEM_USE
    #endif
    #ifndef CUSTOM_SCRIPT
        #define CUSTOM_SCRIPT
    #endif

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

#ifdef PHENOM_SHINY_TWEAK
    #define PHENOM_SHINY_REROLL 3
#endif

#ifdef BLOCK_HM
    #ifndef CUSTOM_SCRIPT
        #define CUSTOM_SCRIPT
    #endif

    #define BLOCKHM_SCRDAT    1801
    #define BLOCKHM_SCRID_MIN 20850
    #define BLOCKHM_SCRID_MAX 20850
    #define BLOCKHM_TXTDAT    805

    #define BLOCKHM_SCR_fail  20850
#endif

#ifdef HIDE_HM
    #define HIDE_DIG
    #define HIDE_TELEPORT
#endif

#if defined(FISHING_CONVENIENT) && defined(FISHING_NO_WAIT)
    #error Please choose either FISHING_NO_WAIT or FISHING_CONVENIENT, not both!
#endif

#ifdef NUZLOCKE
    #ifndef PERMADEATH
        #define PERMADEATH
    #endif
    #ifndef PARTY_KILL
        #define PARTY_KILL
    #endif
    #ifndef FIRST_ENCOUNTER
        #define FIRST_ENCOUNTER
    #endif
    #ifndef FORCE_NICKNAME
        #define FORCE_NICKNAME
    #endif
#endif

#ifdef PARTY_KILL
    #define TPK_FLAG   3037
    #define TPK_TXTDAT 737
#endif

#ifdef FIRST_ENCOUNTER
    #define ZONE_MAX    615
    #define CAP_VAR_MAX (ZONE_MAX >> 4) + 1
    #define ENC1_TXTDAT 738
#endif
