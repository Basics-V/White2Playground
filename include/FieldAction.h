#pragma once
#include "swantypes.h"

typedef GameEvent* (*FieldCommonEventFunc)(Field*, GameSystem*);
#ifndef PW2CODE_INFINITE_REPEL
#define FieldCommonEventTableMax 6
#else
#define FieldCommonEventTableMax 7
#endif
struct FieldCommonEventEntry {
    FieldCommonEventFunc func;
    u32 type;
};

extern FieldCommonEventEntry FIELD_COMMON_EVENTS[];

#ifdef CUSTOM_ITEM_USE
#ifdef PW2CODE_INFINITE_REPEL
#define FieldCommonEventInfiniteRepel 6
extern "C" GameEvent* EventFieldToggleRepel_Create(Field*, GameSystem*);
#endif
#endif
