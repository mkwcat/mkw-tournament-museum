// SaveManagerPage.cpp - Page to prevent the game from loading or unloading a
// scene while the game is currently saving
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

#include "SaveManagerPage.h"
#include "CompFile.h"
#include <mkw/UI/UIPageManager.h>
#include <rvl/os.h>

TYPEINFO_DERIVED(SaveManagerPage, UI::UIPage);

SaveManagerPage::SaveManagerPage()
{
}

SaveManagerPage::~SaveManagerPage()
{
}

static void waitForSaveData()
{
    while (CompFile::sInstance->m_saveDataStatus == CompFile::SAVE_WAITING) {
        OSSleepTicks(0xED4E0);
    }

    while (CompFile::sInstance->m_ghostDataStatus == CompFile::SAVE_WAITING) {
        OSSleepTicks(0xED4E0);
    }
}

void SaveManagerPage::onInit()
{
    m_inputs.init(0, 0);
    setInputManager(&m_inputs);

    waitForSaveData();
}

void SaveManagerPage::onDeinit()
{
    waitForSaveData();

    if (CompFile::sInstance->m_saveDataStatus != CompFile::SAVE_OK ||
        CompFile::sInstance->m_ghostDataStatus != CompFile::SAVE_OK) {
        // TODO: transition to a "save corrupted" screen
        OSReport("SaveManagerPage: m_saveDataStatus: %d, m_saveFsError: %d\n"
                 "                 m_ghostDataStatus: %d, m_ghostFsError: %d\n",
                 CompFile::sInstance->m_saveDataStatus,
                 CompFile::sInstance->m_saveFsError,
                 CompFile::sInstance->m_ghostDataStatus,
                 CompFile::sInstance->m_ghostFsError);
        while (1) {
        }
    }
}

void SaveManagerPage::build(UI::UIPageManager* scene)
{
    SaveManagerPage* page = new SaveManagerPage();
    scene->setPage(SAVEMANAGER_PAGE_ID, page);
    page->init(SAVEMANAGER_PAGE_ID);
}