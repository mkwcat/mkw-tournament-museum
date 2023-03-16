// util.h - Misc functions
//
// SPDX-License-Identifier: MIT

#pragma once
#include <rvl/types.h>

bool isRiivolution();
char getRegionChar();

template <class T>
static inline u32 indexInArray(T* array, T* entry)
{
    return (reinterpret_cast<u32>(entry) - reinterpret_cast<u32>(array)) /
           sizeof(T);
}

bool isTournamentMode();
