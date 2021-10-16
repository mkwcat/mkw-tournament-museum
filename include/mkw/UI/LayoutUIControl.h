// LayoutUIControl.h - UIControl based on NW4R layouts
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
#include "MsgRes.h"
#include "UIControl.h"
#include <rvl/types.h>

namespace UI
{

class SomeAnimation
{
public:
    void doSomething(int, f32);
    u8 fill[0x44];
};

class SomeAnimationContainer
{
public:
    SomeAnimation* getIndex(int);
    u8 fill[0x10];
};

class LayoutUIControl : public UIControl
{
public:
    LayoutUIControl();
    virtual ~LayoutUIControl();

    virtual void _38()
    {
    }

    void setMessage(int msgId, UI::MsgRes::FormatParam* param);
    void setMessage(const char* pane, int msgId,
                    UI::MsgRes::FormatParam* param);
    void setTexture(const char* pane, const char* texture);

    /* 0x098 */ SomeAnimationContainer m_anim;
    /* 0x0A8 */ char fill[0x9C];
    /* 0x144 */ MsgRes m_bmg;
    /* 0x158 */ MsgRes m_commonBmg;
    /* 0x16C */ void* m_iconPane;
    /* 0x170 */ void* m_mainPane;
};
static_assert(sizeof(LayoutUIControl) == 0x174,
              "sizeof(LayoutUIControl) != 0x174");

class CtrlRes
{
public:
    CtrlRes(LayoutUIControl* parent);

    void readFile(const char* lytSection, const char* ctrlName,
                  const char* positionEntry, const char** animations);

    LayoutUIControl* m_parent;
    char fill[0x20];
};

}; // namespace UI