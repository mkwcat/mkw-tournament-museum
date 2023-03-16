// ForcedHandleBypassPage.h - Confirm page that appears when attempting to use
// the wrong controller on a Wii Wheel only tournament
//
// SPDX-License-Identifier: MIT

#pragma once
#include <mkw/UI/Function.h>
#include <mkw/UI/MessageConfirmPopupPage.h>
#include <mkw/UI/PushButton.h>
#include <mkw/UI/UIInputManager.h>
#include <mkw/UI/UIPage.h>
#include <rvl/types.h>

// The page that manages the popup choice that appears when you try to use a
// wrong controller on a Wii Wheel only tournament.
class ForcedHandleBypassPage : public UI::UIPage
{
public:
    static void staticInit();

    ForcedHandleBypassPage();
    virtual ~ForcedHandleBypassPage();

    virtual void onInit();
    virtual void onIn();
    virtual void onChildPageOut();

    void selectYes(UI::MessageConfirmPopupPage* page, UI::PushButton* button);

    static int isWiiWheelPageDisabled();
    static void setWiiWheelPageDisabled(bool set);

protected:
    bool m_noResume;
    bool m_wiiWheelPageDisabled;

    UI::FunctionImp<ForcedHandleBypassPage, UI::MessageConfirmPopupPage*,
                    UI::PushButton*>
      mf_imp_selectYes;
    UI::UIInputManagerMenu m_inputs;

public:
    INSTANTIATE_TYPEINFO;
};
