// SaveManagerPage.h - Page to prevent the game from loading or unloading a
// scene while the game is currently saving
//
// SPDX-License-Identifier: MIT

#pragma once
#include <mkw/UI/UIInputManager.h>
#include <mkw/UI/UIPage.h>
#include <mkw/UI/UIPageManager.h>

#define SAVEMANAGER_PAGE_ID 0x00

class SaveManagerPage : public UI::UIPage
{
public:
    SaveManagerPage();
    virtual ~SaveManagerPage();

    static void build(UI::UIPageManager* scene);

    virtual void onInit();
    virtual void onDeinit();

protected:
    UI::UIInputManager m_inputs;

public:
    INSTANTIATE_TYPEINFO;
};
