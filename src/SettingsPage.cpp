// SettingsPage.cpp - Tournament settings menu
//
// SPDX-License-Identifier: MIT

#include "SettingsPage.h"
#include "CompFile.h"
#include "UI.h"
#include "patch.h"
#include <mkw/RKContext.h>
#include <mkw/UI/MessageWindowPage.h>
#include <mkw/UI/OptionMessageBoxManagerPage.h>
#include <mkw/UI/OptionMessageBoxPromptPage.h>
#include <mkw/UI/PushButton.h>
#include <mkw/UI/SceneBGMController.h>
#include <mkw/UI/UIPage.h>
#include <stdio.h>

TYPEINFO_DERIVED(SettingsPage, UI::UIPage);

enum Button {
    BUTTON_RUMBLE = 0,
    BUTTON_GHOSTDATA = 1,
    BUTTON_LICENSE = 2,
    BUTTON_BACK = -100
};

enum {
    MSG_GHOST_SAVE = 0x2801,
    MSG_GHOST_SAVE_WINDOW = 0x2802,

    MSG_GHOST_SAVE_OPTION = 0x2803,
    MSG_GHOST_SAVE_OPTION_ALL = 0x2803,
    MSG_GHOST_SAVE_OPTION_BEST_TIME = 0x2804,
    MSG_GHOST_SAVE_OPTION_NONE = 0x2805,

    MSG_GHOST_SAVE_MESSAGE_OPTION = 0x2806,
    MSG_GHOST_SAVE_MESSAGE_OPTION_ALL = 0x2806,
    MSG_GHOST_SAVE_MESSAGE_OPTION_BEST_TIME = 0x2807,
    MSG_GHOST_SAVE_MESSAGE_OPTION_NONE = 0x2808
};

SettingsPage::SettingsPage()
  : m_fun_onButtonSelect(this, &SettingsPage::onButtonSelect)
  , m_fun_onBackPress(this, &SettingsPage::onBackPress)
  , m_fun_messageWindowEvent(this, &SettingsPage::messageWindowEvent)
{
    m_nextPage = -1;
}

SettingsPage::~SettingsPage()
{
}

void SettingsPage::onInit()
{
    m_inputs.init(1, 0);
    setInputManager(&m_inputs);
    m_inputs.setScreenWrapSetting(1);

    initControlGroup(5);

    // GCN Controller Rumble
    {
        setControl(0, &m_rumbleButton, 0);
        m_rumbleButton.readLayout("button", "OptionTopButton", "Rumble", 1, 0,
                                  false);
        m_rumbleButton.setSelectFunction(&m_fun_onButtonSelect, 0);
        m_rumbleButton.m_id = BUTTON_RUMBLE;
    }

    // Normally Network Settings
    {
        setControl(1, &m_ghostDataButton, 0);
        m_ghostDataButton.readLayout("button", "OptionTopButton", "Network", 1,
                                     0, false);
        m_ghostDataButton.setSelectFunction(&m_fun_onButtonSelect, 0);
        m_ghostDataButton.setMessage(0x2801, nullptr);
        m_ghostDataButton.m_id = BUTTON_GHOSTDATA;
    }

    // Normally Add Mario Kart Channel
    {
        setControl(2, &m_licenseButton, 0);
        m_licenseButton.readLayout("button", "OptionTopButton",
                                   "ChannelInstall", 1, 0, false);
        m_licenseButton.setSelectFunction(&m_fun_onButtonSelect, 0);
        m_licenseButton.setMessage(0x7DF, nullptr);
        m_licenseButton.m_id = BUTTON_LICENSE;
    }

    setControl(3, &m_backButton, 0);
    m_backButton.initLayout(1);
    m_backButton.setSelectFunction(&m_fun_onButtonSelect, 0);

    setControl(4, &m_titleText, 0);
    m_titleText.initLayout(1);
    m_titleText.setMessage(MID_SETTINGS, 0);

    m_inputs.configureInput(UI::INPUT_BACK, &m_fun_onBackPress, 0, 0);

    // aka options from license settings
    if (RKContext::sInstance->m_scene->m_sceneId == UI::SCENE_INSTALL_CHANNEL) {
        m_licenseButton.setSelected(0);
    } else {
        m_rumbleButton.setSelected(0);
    }
}

void SettingsPage::onButtonSelect(UI::PushButton* button, int r5)
{
    m_nextPage = -1;

    switch (button->m_id) {
    case BUTTON_RUMBLE:
        selectRumble(button);
        break;

    case BUTTON_GHOSTDATA:
        selectGhostData(button);
        break;

    case BUTTON_LICENSE:
        selectLicenseSettings(button);
        break;

    case BUTTON_BACK:
        f32 delay = button->getSelectDelay();
        toNextScene(UI::SCENE_TOURNAMENT, SLIDE_BACK, delay);
        break;
    }
}

void SettingsPage::onBackPress(int r4, int r5)
{
    toNextScene(UI::SCENE_TOURNAMENT, SLIDE_BACK, 0);
}

void SettingsPage::selectRumble(UI::PushButton* button)
{
    UI::OptionMessageBoxManagerPage* page =
      RuntimeTypeInfo::cast<UI::OptionMessageBoxManagerPage*>(
        RKContext::sInstance->m_scene->getPage(0xC6));

    page->m_option = 0;

    m_nextPage = 0xC6;
    f32 delay = button->getSelectDelay();
    toOut(SLIDE_FORWARD, delay);
}

void SettingsPage::selectGhostData(UI::PushButton* button)
{
    m_nextPage = SettingsGhostDataPage::s_pageId;
    f32 delay = button->getSelectDelay();
    toOut(SLIDE_FORWARD, delay);
}

void SettingsPage::selectLicenseSettings(UI::PushButton* button)
{
    UI::SceneBGMControllerInstance->enableBGMPersist();
    f32 delay = button->getSelectDelay();
    toNextScene(UI::SCENE_LICENSE_SETTINGS, SLIDE_FORWARD, delay);
}

void SettingsPage::messageWindowEvent(UI::MessageWindowPage* page, int r5)
{
    UI::SceneBGMControllerInstance->enableBGMPersist();
    page->toNextScene(UI::SCENE_OPTIONS, SLIDE_FORWARD, 0);
}

int SettingsPage::getNextPageID()
{
    return m_nextPage;
}

SettingsGhostDataPage::SettingsGhostDataPage()
  : m_fun_windowOut(this, &SettingsGhostDataPage::windowOut)
  , m_fun_onButtonSelect(this, &SettingsGhostDataPage::onButtonSelect)
  , m_fun_onBackPress(this, &SettingsGhostDataPage::onBackPress)
{
}

SettingsGhostDataPage::~SettingsGhostDataPage()
{
}

void SettingsGhostDataPage::onInit()
{
    m_inputs.init(1, 0);
    setInputManager(&m_inputs);
    m_inputs.setScreenWrapSetting(1);
    m_inputs.configureInput(UI::INPUT_BACK, &m_fun_onBackPress, 0, 0);

    initControlGroup(6);

    for (int i = 0; i < 3; i++) {
        setControl(i, &m_buttons[i], 0);

        char ctrl[16];
        snprintf(ctrl, 15, "Option%d_%d", i, 3);

        m_buttons[i].readLayout("button", "OptionSelectButton", ctrl, 1, 0,
                                false);
        m_buttons[i].setSelectFunction(&m_fun_onButtonSelect, 0);
        m_buttons[i].setMessage(MSG_GHOST_SAVE_OPTION + i, nullptr);
        m_buttons[i].m_id = i;
    }

    setControl(3, &m_titleText, 0);
    m_titleText.initLayout(1);
    m_titleText.setMessage(MSG_GHOST_SAVE, nullptr);

    setControl(4, &m_backButton, 0);
    m_backButton.initLayout(1);
    m_backButton.setSelectFunction(&m_fun_onButtonSelect, 0);

    setControl(5, &m_window, 0);
    m_window.readWindowLayout("message_window", "OptionMessageWindowQuarter",
                              "MessageWindowQuarter");
    m_window.setMessage(MSG_GHOST_SAVE_WINDOW, nullptr);
}

void SettingsGhostDataPage::onIn()
{
    u8 opt = CompFile::sInstance->m_saveData
               .data[RKContext::sInstance->m_98->m_licenseId]
               .ghostSaveMode;

    if (opt > 2)
        opt = 0;

    m_buttons[opt].setSelected(0);
}

void SettingsGhostDataPage::onButtonSelect(UI::PushButton* button, int r5)
{
    f32 delay = button->getSelectDelay();

    if (button->m_id == -100) {
        // Back
        m_nextPage = 0xC0;
        toOut(SLIDE_BACK, delay);
        return;
    }

    if (button->m_id < 0 || button->m_id > 2)
        return;

    int opt = button->m_id;

    UI::MessageWindowNoButtonPage* windowPage =
      RuntimeTypeInfo::cast<UI::MessageWindowNoButtonPage*>(
        RKContext::sInstance->m_scene->getPage(0xC8));
    windowPage->setWindowText(MSG_GHOST_SAVE_MESSAGE_OPTION + opt, nullptr);
    windowPage->m_pressAFunc = &m_fun_windowOut;

    CompFile::sInstance->m_saveData
      .data[RKContext::sInstance->m_98->m_licenseId]
      .ghostSaveMode = opt;
    CompFile::sInstance->requestWriteSaveFile();

    m_nextPage = 0xC8;
    toOut(SLIDE_FORWARD, delay);
}

void SettingsGhostDataPage::onBackPress(int r4, int r5)
{
    m_nextPage = 0xC0;
    toOut(SLIDE_BACK, 0);
}

void SettingsGhostDataPage::windowOut(UI::MessageWindowPage* page, int r5)
{
    UI::SceneBGMControllerInstance->enableBGMPersist();
    toNextScene(UI::SCENE_OPTIONS, SLIDE_FORWARD, 0);
}

int SettingsGhostDataPage::getNextPageID()
{
    return m_nextPage;
}

void LicenseSettings_onButtonBackPress(UI::UIPage* page, UI::PushButton* button)
{
    UI::SceneBGMControllerInstance->enableBGMPersist();
    // aka Options from License Settings
    page->toNextScene(UI::SCENE_INSTALL_CHANNEL, UI::UIPage::SLIDE_BACK,
                      button->getSelectDelay());
}

void LicenseSettings_onBackPress(UI::UIPage* page)
{
    UI::SceneBGMControllerInstance->enableBGMPersist();
    // aka Options from License Settings
    page->toNextScene(UI::SCENE_INSTALL_CHANNEL, UI::UIPage::SLIDE_BACK, 0);
}

void LicenseSelect_optionsButton(UI::PushButton* button)
{
    button->m_hide = true;
    button->m_selectable = 0;
}

extern Instruction<1> Patch_LicenseSettingsBack;
extern Instruction<1> Patch_LicenseSelectOptions;

void SettingsPage::staticInit()
{
    Patch_LicenseSettingsBack.setB(LicenseSettings_onButtonBackPress);
    Patch_LicenseSettingsBack.setB(LicenseSettings_onBackPress, 0xB8 / 4);
    Patch_LicenseSelectOptions.setBL(LicenseSelect_optionsButton);
}
