// SaveManagerPage.cpp - Page to prevent the game from loading or unloading a
// scene while the game is currently saving
//
// SPDX-License-Identifier: MIT

#include "SaveManagerPage.h"
#include "CompFile.h"
#include <mkw/UI/UIPageManager.h>
#include <rvl/os.h>
#include <stdio.h>

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
        // TODO: transition to a "save corrupted" screen in the normal UI system

        char msg[256];

        snprintf(msg, 256,
                 "---- MKWTM ERROR ----\n"
                 "A save data error has occurred.\n"
                 "Error info:\n"
                 "   m_saveDataStatus: %d\n"
                 "   m_saveFsError: %d\n"
                 "   m_ghostDataStatus: %d\n"
                 "   m_ghostFsError: %d\n"
                 "   m_ghostPath: %.128s\n",
                 CompFile::sInstance->m_saveDataStatus,
                 CompFile::sInstance->m_saveFsError,
                 CompFile::sInstance->m_ghostDataStatus,
                 CompFile::sInstance->m_ghostFsError,
                 CompFile::sInstance->m_ghostPath);

        u32 textColor = 0xFFFFFFFF;
        u32 bgColor = 0x000000FF;
        OSFatal(&textColor, &bgColor, msg);

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
