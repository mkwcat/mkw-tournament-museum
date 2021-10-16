// Replay.cpp - Patches for tournament replay mode
//
// Copyright (c) 2021 TheLordScruffy
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "Replay.h"
#include "patch.h"
#include "util.h"
#include <mkw/MenuSet.h>

// in MenuSet::RaceSetting modeFlags, new bit flag!
#define FLAG_REPLAY_BIT 16
#define FLAG_REPLAY (1 << (32 - FLAG_REPLAY_BIT - 1))

bool isTournamentReplayInSetting(MenuSet::RaceSetting* set)
{
    return set->modeFlags & FLAG_REPLAY;
}
bool isTournamentReplay()
{
    return isTournamentReplayInSetting(&MenuSet::sInstance->currentRace);
}

void setupNextRaceInputHook(MenuSet::RaceSetting* nextRace,
                            MenuSet::RaceSetting* lastRace)
{
    if (isTournamentMode() && nextRace->controlKind == 1) {
        nextRace->modeFlags |= FLAG_REPLAY;

        // This means the last race was a replay as well, so skip setting up the
        // replay inputs again.
        if (!(lastRace->modeFlags & FLAG_REPLAY)) {
            nextRace->setupNextRaceInput(lastRace);
        }

        nextRace->controlKind = 0;
        return;
    }

    nextRace->modeFlags &= ~FLAG_REPLAY;
    nextRace->setupNextRaceInput(lastRace);
}

asm void controlKindCheck_RaceFinishReset()
{
    // clang-format off
    nofralloc

    cmpwi   r0, 1
    beqlr-

    mflr    r28
    bl      isTournamentReplay
    mtlr    r28

    cmpwi   r3, 1
    blr
    // clang-format on
}

asm void controlKindCheck_PauseBeforeStart()
{
    // clang-format off
    nofralloc

    // r0 is controlKind
    cmpwi   r0, 1
    beqlr-

    // modeFlags
    lwz     r0, 0x20 + 0xB70(r4)
    xori    r0, r0, FLAG_REPLAY
    rlwinm. r0, r0, 0, FLAG_REPLAY_BIT, FLAG_REPLAY_BIT

    blr
    // clang-format on
}

asm void controlKindCheck_PauseMenuFreeze()
{
    // clang-format off
    nofralloc

    // r0 is controlKind
    cmpwi   r0, 0
    bnelr-

    // modeFlags
    lwz     r0, 0x20 + 0xB70(r3)
    rlwinm. r0, r0, 0, FLAG_REPLAY_BIT, FLAG_REPLAY_BIT

    blr
    // clang-format on
}

asm void controlKindCheck_PauseUpdate()
{
    // clang-format off
    nofralloc

    // r0 is controlKind
    cmpwi   r0, 1
    beqlr-

    // modeFlags
    lwz     r0, 0x20 + 0xB70(r3)
    xori    r0, r0, FLAG_REPLAY
    rlwinm. r0, r0, 0, FLAG_REPLAY_BIT, FLAG_REPLAY_BIT

    blr
    // clang-format on
}

asm void replayRearviewPatch()
{
    // clang-format off
    nofralloc

    lis     r8, sInstance__7MenuSet@ha
    lwz     r8, sInstance__7MenuSet@l(r8)
    // modeFlags & tournament bit
    lwz     r8, 0x20 + 0xB70(r8)
    rlwinm. r8, r8, 0, 29, 29

    // exclude rearview mirror bit
    rlwinm  r4, r0, 0, 27, 31
    beqlr

    // include bit
    rlwinm  r4, r0, 0, 26, 31
    blr
    // clang-format on
}

extern Instruction<1> Patch_ControlKindCheck_RaceFinishReset;
extern Instruction<110> Patch_ControlKindCheck_onPause;
extern Instruction<1> Patch_ControlKindCheck_PauseUpdate;
extern Instruction<1> Patch_SetupReplayInputCall;
extern Instruction<1> Patch_ReplayRearview;

// Ghost stuff
extern Instruction<1> Patch_RKGFileSaveSeed;
extern Instruction<1> Patch_GhostHeaderSaveSeed;

void initReplayMode()
{
    Patch_ControlKindCheck_RaceFinishReset.setBL(
        controlKindCheck_RaceFinishReset);
    Patch_ControlKindCheck_onPause.setBL(controlKindCheck_PauseBeforeStart, 31);
    Patch_ControlKindCheck_onPause.setBL(controlKindCheck_PauseMenuFreeze, 81);
    Patch_ControlKindCheck_PauseUpdate.setBL(controlKindCheck_PauseUpdate);
    Patch_SetupReplayInputCall.setBL(setupNextRaceInputHook);

    Patch_ReplayRearview.setBL(replayRearviewPatch);
}