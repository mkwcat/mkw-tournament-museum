// LeaderboardEntry.h
//
// SPDX-License-Identifier: MIT

#pragma once
#include "GhostData.h"
#include "MiiData.h"
#include <rvl/types.h>

struct LeaderboardEntry {
    MiiData mii; // size 0x4C

    GhostData::RaceTime time; // at 0x4C

    int characterId;
    int vehicleId;
    int controllerId;
};
