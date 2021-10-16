// RaceMenuPage.h - Pause menu and end screen base
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
#include "PushButton.h"
#include "UIInputManager.h"
#include "UIPage.h"
#include <RuntimeTypeInfo.h>
#include <rvl/types.h>

namespace UI
{

namespace RaceMenu
{
enum E
{
    ButtonContinue = 0,
    ButtonQuit = 1,
    ButtonRestart = 2,
    ButtonRetry = 3, // "ButtonRestart"
    ButtonReplay = 4,
    ButtonChangeCourse = 5,
    ButtonChangeCharacter = 6,
    ButtonNext = 7,
    ButtonRanking = 8,
    ButtonContinueReplay = 9,
    ButtonRestartReplay = 10,
    ButtonQuitReplay = 11,
    ButtonContinue2 = 12,
    ButtonQuit2 = 13,
    ButtonBattleGhost = 14,
    ButtonRestart3 = 15,
    ButtonContinue3 = 16,
    ButtonQuit3 = 17,
    ButtonChangeMission = 18,
    ButtonSend = 19,
    ButtonNoSend = 20,
    ButtonGoRanking = 21,
    ButtonNotGoRanking = 22,
    ButtonConfirmContinue = 23,
    ButtonConfirmQuit = 24,
    ButtonSendRecord = 25,
    ButtonSend2 = 26,
    ButtonNoSend2 = 27,
    ButtonFriendGhostBattle = 28,
    ButtonGoFriendRoom = 29,
    ButtonNotGoFriendRoom = 30,
    ButtonNextGhost = 31,
    ButtonYes = 32,
    ButtonNo = 33,
    ButtonQuit4 = 34,
    ButtonYes2 = 35,
    ButtonNo2 = 36,
};
} // namespace RaceMenu

class RaceMenuPage : public UIPage
{
public:
    RaceMenuPage();
    virtual ~RaceMenuPage();

    virtual int getNextPageID(); // vt + 0x10
    virtual void setNextPageID(int page); // vt + 0x64

    virtual void onInit(); // vt + 0x28
    virtual void onDeinit(); // vt + 0x2C
    virtual void onIn(); // vt + 0x30
    virtual void onOut(); // vt + 0x34
    virtual void _38();
    virtual void _40();
    virtual void onUpdateEnd();

    virtual int _68() = 0; // load from 0x340?
    virtual int getButtonCount() const = 0; // vt + 0x6C
    virtual const int* getButtonList() const = 0; // vt + 0x70
    virtual bool isPauseMenu() const = 0;
    virtual const char* getButtonCtrlName() const = 0; // vt + 0x78

    u8 fill[0xA8];

    int m_nextPage;
    FunctionImp<RaceMenuPage, PushButton*, int> m_ptr_selectEvent;
    FunctionImp<RaceMenuPage, int, int> m_ptr_108;

    UIInputManagerMenu m_inputs; // 0x118

    INSTANTIATE_TYPEINFO;
};
static_assert(sizeof(RaceMenuPage) == 0x33C, "sizeof(RaceMenuPage) != 0x33C");

} // namespace UI