// SceneBGMController.h - Perhaps a bad name, controls loading the game's sound
//
// SPDX-License-Identifier: MIT

#pragma once
#include <rvl/types.h>

namespace UI
{

extern class SceneBGMController
{
public:
    /* BGM continues playing through scene transition */
    void enableBGMPersist();
}* SceneBGMControllerInstance;

} // namespace UI
