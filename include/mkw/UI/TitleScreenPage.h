// TitleScreenPage.h
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
#include "LayoutUIControl.h"
#include "UIPage.h"
#include "UIInputManager.h"
#include <rvl/types.h>

namespace UI
{

class TitleScreenPage : public UIPage
{
public:
    /* 0x8063AA08 */
    TitleScreenPage();
    virtual ~TitleScreenPage();

    void hideBackground(bool value)
    {
        m_background.m_hide = value;
    }

protected:
    /* 0x044 */ UIInputManager m_inputs;
    /* 0x054 */ LayoutUIControl m_pressStart; // actually CtrlMenuPressStart
    /* 0x1C8 */ LayoutUIControl m_background;
    u8 unk[0x14];
};
static_assert(sizeof(TitleScreenPage) == 0x350,
              "sizeof(TitleScreenPage) != 0x350");

} // namespace UI