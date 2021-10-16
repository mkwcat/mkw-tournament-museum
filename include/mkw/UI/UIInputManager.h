// UIInputManager.h - Class(es) used by UIPage to handle controller inputs
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
#include "Function.h"
#include <rvl/types.h>

namespace UI
{

enum InputIndex
{
    INPUT_BACK = 1,
    INPUT_START = 2
};

class UIInputManager
{
public:
    UIInputManager();
    virtual void _8();
    virtual ~UIInputManager();
    virtual void init(int, int);
    virtual void _14();
    virtual void _18();
    virtual void _1C();
    virtual void _20();
    virtual void _24();
    virtual void _28();
    virtual void _2C();
    virtual void _30();
    virtual void _34();

    u32 m_4;
    u32 m_8;
    u8 m_C;
    u8 m_D;
    u8 m_E;
    u8 m_F;
};
static_assert(sizeof(UIInputManager) == 0x10, "sizeof(UIInputManager) != 0x10");

class UIInputManagerMenu : public UIInputManager
{
public:
    UIInputManagerMenu();
    virtual ~UIInputManagerMenu();

    void configureInput(InputIndex type, FunctionBase<int, int>* func, u8 r6,
                        u8 r7);

    u8 fill[0xC];
    FunctionBase<int, int>* m_input[9];
    u8 m_40[9];
    u8 m_49[9];
    u8 m_52;
    u8 m_53;
    u8 fill2[0x1CC];
    u32 m_220;

    // From Kevin
    void setScreenWrapSetting(int type);
};
static_assert(sizeof(UIInputManagerMenu) == 0x224,
              "sizeof(UIInputManagerMenu) != 0x224");

class UIInputManagerRace : public UIInputManager
{
public:
    /* 0x805EF240 */
    UIInputManagerRace();
    u8 fill[0x134];
};
static_assert(sizeof(UIInputManagerRace) == 0x144,
              "sizeof(UIInputManagerRace) != 0x144");

} // namespace UI