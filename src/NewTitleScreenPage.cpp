// NewTitleScreenPage.cpp - MKWTM Title Screen
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

#include "NewTitleScreenPage.h"
#include <mkw/RKContext.h>
#include <mkw/UI/LayoutUIControl.h>
#include <patch.h>

TYPEINFO_DERIVED(NewTitleScreenPage, UI::UIPage);

void NewTitleScreenPage::onInit()
{
    m_inputs.init(0, 0);
    setInputManager(&m_inputs);

    initControlGroup(3);

    setControl(0, &m_pressStart, 0);
    m_pressStart.initLayout();

    {
        setControl(1, &m_logo, 0);
        UI::CtrlRes ctrl(&m_logo);
        ctrl.readFile("title", "TitleLogo", "TitleLogo", nullptr);
    }
    {
        setControl(2, &m_copyright, 0);
        UI::CtrlRes ctrl(&m_copyright);
        ctrl.readFile("title", "Copyright", "Copyright", nullptr);
    }

    m_pressStart.m_useTransAnim = true;
    m_pressStart.m_transDelay = 2;
}

// Menu overlay fade
const int sFadeFrameCount = 10;

void NewTitleScreenPage::onIn()
{
    if (m_slideDir == SLIDE_FORWARD) {
        m_overlayFadeFrame = 0;
    } else {
        m_overlayFade = true;
        m_overlayFadeFrame = sFadeFrameCount;
    }

    TitleScreenPage::onIn();
}

void NewTitleScreenPage::onUpdateBegin()
{
    UI::UIPage* bgPage = RKContext::sInstance->m_scene->getPage(0x5E);
    UI::UIControl* bgTopControl = bgPage->m_children.m_children[0];
    UI::UIControl* bgBottomControl = bgPage->m_children.m_children[1];

    if (!m_overlayFade) {
        bgTopControl->m_hide = true;
        bgTopControl->m_realPos.alpha = 0;
        bgBottomControl->m_hide = true;
        bgBottomControl->m_realPos.alpha = 0;
        return;
    }

    if (m_slideDir == SLIDE_FORWARD) {
        if (m_overlayFadeFrame >= sFadeFrameCount) {
            bgTopControl->m_realPos.alpha = 255;
            bgTopControl->m_realPos.alpha = 255;
            return;
        }
        m_overlayFadeFrame++;
    } else {
        if (m_overlayFadeFrame <= 0) {
            bgTopControl->m_realPos.alpha = 0;
            bgTopControl->m_realPos.alpha = 0;
            return;
        }
        m_overlayFadeFrame--;
    }

    float alpha = (255 / (float)sFadeFrameCount) * m_overlayFadeFrame;
    bgTopControl->m_realPos.alpha = (u8)alpha;
    bgBottomControl->m_realPos.alpha = (u8)alpha;
}

void titleScreen_toOut(NewTitleScreenPage* page, UI::UIPage::TransitionDir dir,
                       float delay)
{
    page->toOut(dir, delay);

    UI::UIPage* bgPage = RKContext::sInstance->m_scene->getPage(0x5E);

    UI::UIControl* bgTopControl = bgPage->m_children.m_children[0];
    bgTopControl->m_hide = false;
    bgTopControl->m_realPos.alpha = 0;
    UI::UIControl* bgBottomControl = bgPage->m_children.m_children[1];
    bgBottomControl->m_hide = false;
    bgBottomControl->m_realPos.alpha = 0;

    page->m_overlayFade = true;
    page->m_overlayFadeFrame = 0;
}

extern Instruction<1> Patch_TitleScreenOnIn;
extern Instruction<1> Patch_TitleScreenToOut;
void NewTitleScreenPage::staticInit()
{
    Patch_TitleScreenOnIn.setNop();
    Patch_TitleScreenToOut.setBL(titleScreen_toOut);
}