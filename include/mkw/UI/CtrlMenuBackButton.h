// CtrlMenuBackButton.h - On screen back button
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
#include <RuntimeTypeInfo.h>
#include <rvl/types.h>

namespace UI
{

class CtrlMenuBackButton : public PushButton
{
public:
    CtrlMenuBackButton() : msgId(0x7D1), m_258(0), m_25C(0)
    {
    }

    virtual void onInit();
    virtual void onCalc();
    virtual void _20();
    virtual const char* getTypeName();

    void initLayout(int playerCount)
    {
        readLayout("button", "Back", "ButtonBack", playerCount, 1, true);
        m_id = -100;
        m_7C = 400;
    }

    int msgId;
    int m_258;
    f32 m_25C;
    int m_260;

    INSTANTIATE_TYPEINFO;
};

static_assert(sizeof(CtrlMenuBackButton) == 0x264,
              "sizeof(CtrlMenuBackButton) != 0x264");

} // namespace UI