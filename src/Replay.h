// Replay.h - Patches for tournament replay mode
//
// SPDX-License-Identifier: MIT

#pragma once
#include <mkw/MenuSet.h>
#include <rvl/types.h>

void initReplayMode();
// Extern C for ASM block
EXTERN_C_START
bool isTournamentReplayInSetting(MenuSet::RaceSetting* set);
bool isTournamentReplay();
EXTERN_C_END
