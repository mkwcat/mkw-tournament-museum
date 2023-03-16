// CtrlMenuPressStart.h - Press start text on the Title Screen
//
// SPDX-License-Identifier: MIT

#pragma once
#include "LayoutUIControl.h"

namespace UI
{

class CtrlMenuPressStart : public LayoutUIControl
{
public:
    INSTANTIATE_TYPEINFO;

    CtrlMenuPressStart(); // always inlined I think
    virtual ~CtrlMenuPressStart();

    /* 0x807E9CD0 */
    void initLayout();
};

} // namespace UI
