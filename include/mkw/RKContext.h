// RKContext.h - A weird collection of mostly unrelated things
//
// SPDX-License-Identifier: MIT

#pragma once
#include <mkw/UI/UIPageManager.h>

class RKContext
{
public:
    static RKContext* sInstance;

    void setNextScene(int nextScene, int r5);
    void startSceneTransition(int delay, u32 rgbaBgColor);

    UI::UIPageManager* m_scene;
    u8 fill_0x4[0x94];

    struct {
        u8 fill_0x0[0x4B4];
        int m_leaderboardRank;
        u8 fill_0x4B8[0x4E8 - 0x4B8];
        u8 m_licenseId;
        u8 fill_0x4E9[0x510 - 0x4E9];
    }* m_98;
};
