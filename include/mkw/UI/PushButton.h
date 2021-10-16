// PushButton.h - Standard multi purpose on screen menu button
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
#include "LayoutUIControl.h"
#include <rvl/types.h>

namespace UI
{

class ButtonInputBase
{
    u32 fill[2]; // some struct, has its own constructor
public:
    ButtonInputBase();
    virtual ~ButtonInputBase();

    u8 fill2[0x78];
};

class PushButton : public LayoutUIControl
{
public:
    PushButton();
    virtual ~PushButton();
    virtual void _3C();
    virtual void onFreeToSelect();
    virtual void onSelectToFree();
    virtual void onSelect();

    void setSelectFunction(FunctionBase<PushButton*, int>* func, int);
    void setFreeToSelectFunction(FunctionBase<PushButton*, int>* func);

    void readLayout(const char* lytSection, const char* ctrlName,
                    const char* positionEntry, int playerCount, int,
                    bool pointerExclusive);

    void setSelected(int player);
    void freeToSelect(int player);

    f32 getSelectDelay();

    /* 0x174 */ ButtonInputBase m_inputs;

protected:
    FunctionImp<PushButton, int, int> mf_imp_defaultFreeToSelect;
    FunctionImp<PushButton, int, int> mf_imp_defaultSelectToFree;
    FunctionImp<PushButton, int, int> mf_imp_defaultSelect;

public:
    /* 0x234 */ Function<PushButton*, int> mf_onFreeToSelect;
    /* 0x238 */ Function<PushButton*, int> mf_onSelectToFree;
    /* 0x23C */ Function<PushButton*, int> mf_onSelect;

    /* 0x240 */ u32 m_id;
    /* 0x244 */ int m_selectable;

    /* 0x248 */ void* m_somePane;
    /* 0x24C */ void* m_somePane2;

    /* 0x250 */ s32 m_selectSoundId;
};

static_assert(sizeof(PushButton) == 0x254, "sizeof(PushButton) != 0x254");

} // namespace UI