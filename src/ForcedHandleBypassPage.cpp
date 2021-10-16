// ForcedHandleBypassPage.cpp - Confirm page that appears when attempting to use
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

#include "ForcedHandleBypassPage.h"
#include "CompFile.h"
#include <mkw/RKContext.h>
#include <patch.h>

TYPEINFO_DERIVED(ForcedHandleBypassPage, UI::UIPage);

ForcedHandleBypassPage::ForcedHandleBypassPage()
    : mf_imp_selectYes(this, &ForcedHandleBypassPage::selectYes)
{
    m_noResume = false;
    m_wiiWheelPageDisabled = false;
}

ForcedHandleBypassPage::~ForcedHandleBypassPage()
{
}

void ForcedHandleBypassPage::onInit()
{
    CompFile::sInstance->m_forceHandleDisabled = false;

    m_inputs.init(0, 0);
    setInputManager(&m_inputs);
}

void ForcedHandleBypassPage::onIn()
{
    UI::MessageConfirmPopupPage* msgPage =
        RuntimeTypeInfo::cast<UI::MessageConfirmPopupPage*>(
            RKContext::sInstance->m_scene->getPage(0x4E));

    msgPage->configMessage(0x2800, nullptr);
    msgPage->configOption(0, 0xFAC, nullptr, 1, &mf_imp_selectYes);
    msgPage->configOption(1, 0xFAD, nullptr, -1, nullptr);
    m_noResume = false;
    insertPage(0x4E, SLIDE_FORWARD);
}

void ForcedHandleBypassPage::selectYes(UI::MessageConfirmPopupPage* page,
                                       UI::PushButton* button)
{
    CompFile::sInstance->m_forceHandleDisabled = true;

    const int sceneId = RKContext::sInstance->m_scene->m_sceneId;
    if (sceneId == 0x88) {
        // Normal tournament intro
        RKContext::sInstance->setNextScene(0x2D, 0);
    } else if (sceneId == 0x89) {
        // For bosses specifically
        RKContext::sInstance->setNextScene(0x1D, 0);
    }

    f32 delay = button->getSelectDelay();
    RKContext::sInstance->startSceneTransition((int)delay, 0x000000FF);

    UI::UIPage* lastPage = RKContext::sInstance->m_scene->getPage(0xBA);
    lastPage->toOut(UI::UIPage::SLIDE_FORWARD, delay);

    m_noResume = true;
}

void ForcedHandleBypassPage::onChildPageOut()
{
    UI::UIPage* lastPage = RKContext::sInstance->m_scene->getPage(0xBA);
    if (!m_noResume) {
        // These calls emulate two functions required to dereference the
        // current controller
        lastPage->onIn();
        lastPage->_3C();
        m_wiiWheelPageDisabled = false;
    }
    toOut(UI::UIPage::SLIDE_FORWARD, 0);
}

int ForcedHandleBypassPage::isWiiWheelPageDisabled()
{
    ForcedHandleBypassPage* page =
        RuntimeTypeInfo::cast<ForcedHandleBypassPage*>(
            RKContext::sInstance->m_scene->getPage(0x87));
    return page->m_wiiWheelPageDisabled;
}
void ForcedHandleBypassPage::setWiiWheelPageDisabled(bool set)
{
    ForcedHandleBypassPage* page =
        RuntimeTypeInfo::cast<ForcedHandleBypassPage*>(
            RKContext::sInstance->m_scene->getPage(0x87));
    page->m_wiiWheelPageDisabled = set;
}

void wiiWheelPageRejectController(UI::UIPage* page)
{
    if (ForcedHandleBypassPage::isWiiWheelPageDisabled())
        return;

    ForcedHandleBypassPage::setWiiWheelPageDisabled(true);
    page->insertPage(0x87, UI::UIPage::SLIDE_FORWARD);
}

extern Instruction<11> Patch_WiiWheelOnlyPage;
void ForcedHandleBypassPage::staticInit()
{
    Patch_WiiWheelOnlyPage.setBL(wiiWheelPageRejectController);
    Patch_WiiWheelOnlyPage.setB(&Patch_WiiWheelOnlyPage.m_instr[11], 1);
}