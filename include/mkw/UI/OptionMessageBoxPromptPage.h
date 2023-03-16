// OptionMessageBoxPromptPage.h - A message box with two or three buttons used
// on the options menu as page 0xC3 and 0xC4
//
// SPDX-License-Identifier: MIT

#pragma once
#include "CtrlMenuBackButton.h"
#include "CtrlMenuPageTitleText.h"
#include "Function.h"
#include "MessageWindowControl.h"
#include "PushButton.h"
#include "UIInputManager.h"
#include "UIPage.h"

namespace UI
{

class OptionMessageBoxPromptPage : public UIPage
{
public:
    /* 0x805FE5F8 */
    OptionMessageBoxPromptPage();
    /* 0x805FE728 */
    virtual ~OptionMessageBoxPromptPage();
    /* vtable: 0x808BA278 */

    /* 0x805FE7D4 */
    virtual void onInit();
    /* 0x805FEA58 */
    virtual void onIn();
    /* 0x805FEA88 */
    virtual void onChildPageOut();

protected:
    /* 0x044 */ FunctionImp<OptionMessageBoxPromptPage, PushButton*, int>
      m_fun_0x44;
    /* 0x058 */ FunctionImp<OptionMessageBoxPromptPage, int, int> m_fun_0x58;

    /* 0x06C */ UIInputManagerMenu m_inputs;

public:
    /* 0x290 */ CtrlMenuPageTitleText m_titleText;
    /* 0x404 */ MessageWindowControl m_window;
    /* 0x578 */ PushButton m_buttons[3];
    /* 0xC74 */ CtrlMenuBackButton m_backButton;

    // If the confirm message ID is not zero, selecting the option will make a
    // MessageConfirmPopupPage appear with the window text set to the specific
    // message ID.
    /* 0xED8 */ int m_buttonConfirmMsgIds[3];
    // page 0xC3 = 2, page 0xC4 = 3
    /* 0xEE4 */ int m_buttonCount;
    // When a button is selected, this is set to the button ID.
    /* 0xEE8 */ int m_selectedButton;
    // The button to default selected when the page shows.
    /* 0xEEC */ u8 m_defaultButton;

    /* func: 0x80601034, typeinfo: 0x809C1CF4 */
    INSTANTIATE_TYPEINFO;
};

static_assert(sizeof(OptionMessageBoxPromptPage) == 0xEF0,
              "sizeof(OptionMessageBoxPromptPage) != 0xEF0");

} // namespace UI
