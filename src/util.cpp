// util.cpp - Misc functions
//
// SPDX-License-Identifier: MIT

#include "util.h"
#include <mkw/MenuSet.h>
#include <string.h>

extern const char diResNameStr[];

bool isRiivolution()
{
    if (strcmp(diResNameStr, "/dev/do") == 0)
        return true;

    return false;
}

char getRegionChar()
{
    return *(char*) 0x80000003;
}

bool isTournamentMode()
{
    return MenuSet::sInstance->currentRace.modeFlags &
           MenuSet::RaceSetting::FLAG_TOURNAMENT;
}
