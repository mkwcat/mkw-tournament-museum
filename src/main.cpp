// main.cpp - Program entry point
//
// SPDX-License-Identifier: MIT

#include "CompFile.h"
#include "File.h"
#include "Replay.h"
#include "UI.h"
#include "util.h"

void MKWTMMain()
{
    initMenu();
    initReplayMode();
    initCompFilePatches();
}
