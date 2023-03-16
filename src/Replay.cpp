// Replay.cpp - Patches for tournament replay mode
//
// SPDX-License-Identifier: MIT

#include "Replay.h"
#include "patch.h"
#include "util.h"
#include <asm.h>
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

// clang-format off
ASM_FUNCTION(void controlKindCheck_RaceFinishReset(),  
    cmpwi   R0, 1;
    beqlr-;

    mflr    R28;
    bl      isTournamentReplay;
    mtlr    R28;

    cmpwi   R3, 1;
    blr;
)

ASM_FUNCTION(void controlKindCheck_PauseBeforeStart(),
    // r0 is controlKind
    cmpwi   R0, 1;
    beqlr-;

    // modeFlags
    lwz     R0, 0x20 + 0xB70(R4);
    xori    R0, R0, FLAG_REPLAY;
    rlwinm. R0, R0, 0, FLAG_REPLAY_BIT, FLAG_REPLAY_BIT;

    blr;
)

ASM_FUNCTION(void controlKindCheck_PauseMenuFreeze(),
    // r0 is controlKind
    cmpwi   R0, 0;
    bnelr-;

    // modeFlags
    lwz     R0, 0x20 + 0xB70(R3);
    rlwinm. R0, R0, 0, FLAG_REPLAY_BIT, FLAG_REPLAY_BIT;

    blr;
)

ASM_FUNCTION(void controlKindCheck_PauseUpdate(),
    // r0 is controlKind
    cmpwi   R0, 1;
    beqlr-;

    // modeFlags
    lwz     R0, 0x20 + 0xB70(R3);
    xori    R0, R0, FLAG_REPLAY;
    rlwinm. R0, R0, 0, FLAG_REPLAY_BIT, FLAG_REPLAY_BIT;

    blr;
)

ASM_FUNCTION(void replayRearviewPatch(),
    lis     R8, sInstance__7MenuSet@ha;
    lwz     R8, sInstance__7MenuSet@l(R8);
    // modeFlags & tournament bit
    lwz     R8, 0x20 + 0xB70(R8);
    rlwinm. R8, R8, 0, 29, 29;

    // exclude rearview mirror bit
    rlwinm  R4, R0, 0, 27, 31;
    beqlr;

    // include bit
    rlwinm  R4, R0, 0, 26, 31;
    blr;
)
// clang-format on

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
