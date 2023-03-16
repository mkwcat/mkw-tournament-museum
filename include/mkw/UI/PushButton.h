// PushButton.h - Standard multi purpose on screen menu button
//
// SPDX-License-Identifier: MIT

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

static_assert(sizeof(ButtonInputBase) == 0x84,
              "sizeof(ButtonInputBase) != 0x84");

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

    /* 0x240 */ s32 m_id;
    /* 0x244 */ int m_selectable;

    /* 0x248 */ void* m_somePane;
    /* 0x24C */ void* m_somePane2;

    /* 0x250 */ s32 m_selectSoundId;
};

static_assert(sizeof(PushButton) == 0x254, "sizeof(PushButton) != 0x254");

} // namespace UI
