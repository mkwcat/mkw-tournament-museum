// ForcedHandleBypassPage.h - Confirm page that appears when attempting to use
// the wrong controller on a Wii Wheel only tournament
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