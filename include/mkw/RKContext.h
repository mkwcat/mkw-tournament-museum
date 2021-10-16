// RKContext.h - A weird collection of mostly unrelated things
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
    } * m_98;
};