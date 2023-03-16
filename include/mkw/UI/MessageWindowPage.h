// MessageWindowPage.h - Base for message window pages
//
// SPDX-License-Identifier: MIT

#pragma once
#include "CtrlMenuPageTitleText.h"
#include "Function.h"
#include "MessageWindowControl.h"
#include "MsgRes.h"
#include "RaceHudPage.h"
#include "UIInputManager.h"
#include "UIPage.h"

namespace UI
{

class MessageWindowPage : public UIPage
{
public:
    // always inlined probably
    MessageWindowPage();
    /* 0x805F8DE0 */
    virtual ~MessageWindowPage();

    /* 0x805F8E48 */
    virtual void onInit();
    /* 0x805F8EB8 */
    virtual void onIn();
    /* 0x805F8EDC */
    virtual void onUpdateEnd();

    /* 0x805F8F40 */
    virtual void resetWindowText();
    virtual void setWindowText(int msgId, MsgRes::FormatParam* param) = 0;
    virtual void _6C();

protected:
    /* 0x044 */ UIInputManagerRace m_inputs;

public:
    /* 0x188 */ Function<MessageWindowPage*, int> m_pressAFunc;

protected:
    /* 0x18C */ FunctionImp<MessageWindowPage, MessageWindowPage*, int>
      m_fun_pressAEvent;
    /* 0x1A0 */ u32 unk_0x1A0;
    /* 0x1A4 */ u32 unk_0x1A4;

public:
    /* func: 0x805F9698, typeinfo: 0x809C1CB0 */
    INSTANTIATE_TYPEINFO;
};

static_assert(sizeof(MessageWindowPage) == 0x1A8,
              "sizeof(MessageWindowPage) != 0x1A8");

class MessageWindowNoButtonPage : public MessageWindowPage
{
public:
    /* 0x1A8 */ CtrlMenuPageTitleText m_titleText;
    /* 0x31C */ MessageWindowControl m_messageWindow;
    /* 0x490 */ LayoutUIControl m_control0x490;
    /* 0x604 */ u32 m_nextPage;

    /* 0x805F9474 */
    virtual void onInit();

    /* 0x805F95C0 */
    virtual void resetWindowText();
    /* 0x805F9620 */
    void setTitleText(int msgId, MsgRes::FormatParam* param);
    /* 0x805F9628 */
    virtual void setWindowText(int msgId, MsgRes::FormatParam* param);
    /* 0x805F9630 */
    virtual void _6C();

    /* 0x805F9678 */
    virtual int getNextPageID();

public:
    // For some reason this class doesn't include MessageWindowPage as inherited
    /* func: 0x805F9680, typeinfo: 0x809C1CB8 */
    INSTANTIATE_TYPEINFO;
};

static_assert(sizeof(MessageWindowNoButtonPage) == 0x608,
              "sizeof(MessageWindowNoButtonPage) != 0x608");

} // namespace UI
