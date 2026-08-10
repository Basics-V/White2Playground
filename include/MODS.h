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

#ifdef NUZLOCKE
#define NO_REVIVE
#define PERMADEATH
#define EXCLUSIVE_CAPTURE_LOCATION
#endif
