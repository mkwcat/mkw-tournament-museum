// SheetSelectControl.h - On screen menu arrow buttons
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
#include "UIControl.h"
#include "UIInputManager.h"
#include <rvl/types.h>

namespace UI
{

class SheetSelectControl : public UIControl
{
public:
    class SheetSelectButton : public LayoutUIControl
    {
    public:
        /* Like PushButton with some differences */
        SheetSelectButton(); // fake! this is always inlined actually

        /* 0x174 */ ButtonInputBase m_inputs;

        FunctionImp<SheetSelectControl, int, int> mf_imp_1F8;
        FunctionImp<SheetSelectControl, int, int> mf_imp_20C;
        FunctionImp<SheetSelectControl, int, int> mf_imp_220;

        int m_id;
        int m_selectable;

        bool m_23C;
        void* m_somePane;
        void* m_somePane2;
    };
    static_assert(sizeof(SheetSelectButton) == 0x248,
                  "sizeof(SheetSelectButton) != 0x248");

    /* 0x80635EC4 */
    SheetSelectControl();
    /* 0x8063607C */
    virtual ~SheetSelectControl();

    /* 0x80636120 */
    void readLayout(const char* lytSection, const char* ctrlName1,
                    const char* positionEntry1, const char* ctrlName2,
                    const char* positionEntry2, int playerCount, int,
                    bool pointerExclusive);

    /* 0x80636264 */
    void setEnabledArrows(bool leftEnabled, bool rightEnabled);

    /* 0x098 */ Function<SheetSelectControl*, int> mf_onSelectRight;
    /* 0x09C */ Function<SheetSelectControl*, int> mf_onSelectLeft;
    /* 0x0A0 */ u32 m_A0;
    /* 0x0A4 */ u32 m_A4;
    /* 0x0A8 */ SheetSelectButton m_buttonRight;
    /* 0x2F0 */ SheetSelectButton m_buttonLeft;
};
static_assert(sizeof(SheetSelectControl) == 0x538,
              "sizeof(SheetSelectControl) != 0x538");

} // namespace UI