// TitleScreenPage.h
//
// SPDX-License-Identifier: MIT

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
