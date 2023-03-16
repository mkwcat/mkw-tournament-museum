// CtrlMenuBackButton.h - On screen back button
//
// SPDX-License-Identifier: MIT

#pragma once
#include "PushButton.h"
#include <RuntimeTypeInfo.h>
#include <rvl/types.h>

namespace UI
{

class CtrlMenuBackButton : public PushButton
{
public:
    CtrlMenuBackButton()
      : msgId(0x7D1)
      , m_258(0)
      , m_25C(0)
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
