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
#include "CtrlMenuPressStart.h"
#include "LayoutUIControl.h"
#include "UIInputManager.h"
#include "UIPage.h"
#include <RuntimeTypeInfo.h>
#include <rvl/types.h>

namespace UI
{

class TitleScreenPage : public UIPage
{
public:
    /* 0x8063AA08 */
    TitleScreenPage();
    /* 0x8063AAE4 */
    virtual ~TitleScreenPage();

    /* vtable: 0x808BEEA8 */

    /* 0x8063C398 */
    virtual int getNextPageID();

    /* 0x8063AB6C */
    virtual void onInit();
    /* 0x8063AD60 */
    virtual void onDeinit();
    /* 0x8063AD64 */
    virtual void onIn();

    /* 0x8063ADE4 */
    virtual void _38();
    /* 0x8063AE94 */
    virtual void _3C();
    /* 0x8063AEE0 */
    virtual void _40();
    /* 0x8063AF90 */
    virtual void _44();

    /* 0x8063AFC8 */
    virtual void onUpdateEnd();

    /* 0x8063B124 */
    virtual void onChildPageOut();

protected:
    /* 0x044 */ UIInputManager m_inputs;
    /* 0x054 */ CtrlMenuPressStart m_pressStart;
    /* 0x1C8 */ LayoutUIControl m_background; // actually "TitleImage"
    /* 0x33C */ u32 unk_0x33C;
    /* 0x340 */ int m_nextPage;
    /* 0x344 */ u32 unk_0x344;
    /* 0x348 */ u32 unk_0x348;
    /* 0x34C */ u32 unk_0x34C;

public:
    INSTANTIATE_TYPEINFO;
};
static_assert(sizeof(TitleScreenPage) == 0x350,
              "sizeof(TitleScreenPage) != 0x350");

} // namespace UI