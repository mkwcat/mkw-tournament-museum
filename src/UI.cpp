// UI.cpp - Manage scene and patch UI
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

#include "UI.h"
#include "ForcedHandleBypassPage.h"
#include "RaceMenu.h"
#include "Replay.h"
#include "SaveManagerPage.h"
#include "SelectionPage.h"
#include "SettingsPage.h"
#include "patch.h"
#include "util.h"
#include <mkw/MenuSet.h>
#include <mkw/RKContext.h>
#include <mkw/Sound.h>
#include <mkw/UI/PushButton.h>
#include <mkw/UI/TitleScreenPage.h>
#include <mkw/UI/UIPage.h>
#include <mkw/UI/UIPageManager.h>

// use a static variable for this I guess
s32 s_eventExplanation_nextPage = -1;

void eventExplanationSelectEvent(UI::UIPage* page, UI::PushButton* button,
                                 int r5)
{
    float delay = button->getSelectDelay();

    if (button->m_id == 2) {
        // Start/Next button
        s_eventExplanation_nextPage = 0xB7;
        page->toOut(UI::UIPage::SLIDE_FORWARD, delay);
        return;
    }
    if (button->m_id == 3) {
        // Back button
        s_eventExplanation_nextPage = 0x8C;
        page->toOut(UI::UIPage::SLIDE_BACK, delay);
        return;
    }
}

void eventExplanationBackEvent(UI::UIPage* page, int r4, int r5)
{
    s_eventExplanation_nextPage = 0x8C;
    page->toOut(UI::UIPage::SLIDE_BACK, 0);
}

s32 eventExplanationGetNextPage(UI::UIPage* page)
{
    return s_eventExplanation_nextPage;
}

void buildPagesReplace(UI::UIPageManager* scene, int id)
{
    switch (id) {
    case UI::SCENE_TEST_6:
        scene->buildPage(0x00);
        break;

    case UI::SCENE_TEST_7:
        scene->buildPage(0x00);
        break;

    case UI::SCENE_TEST_8:
        scene->buildPage(0x00);
        break;

    case UI::SCENE_TEST_9:
        scene->buildPage(0x00);
        break;

    case UI::SCENE_TEST_A:
        scene->buildPage(0x00);
        break;

    case UI::SCENE_TEST_B:
        scene->buildPage(0x00);
        break;

    case UI::SCENE_TEST_C:
        scene->buildPage(0x00);
        break;

    case UI::SCENE_TEST_D:
        scene->buildPage(0x00);
        break;

    case UI::SCENE_TEST_E:
        scene->buildPage(0x00);
        break;

    case UI::SCENE_TEST_F:
        scene->buildPage(0x00);
        break;

    case UI::SCENE_CREATE_NEW_SAVE:
        scene->buildPage(0x03);
        scene->buildPage(0x4F);
        scene->buildPage(0x5D);
        break;

    case UI::SCENE_CORRUPTED_SAVE:
        scene->buildPage(0x03);
        scene->buildPage(0x4F);
        scene->buildPage(0x53);
        scene->buildPage(0x5D);
        break;

    case UI::SCENE_COUNTRY_CHANGED:
        scene->buildPage(0x03);
        scene->buildPage(0x4F);
        scene->buildPage(0x53);
        scene->buildPage(0x5D);
        break;

    case UI::SCENE_GAME_CANNOT_BE_SAVED:
        scene->buildPage(0x04);
        scene->buildPage(0x53);
        scene->buildPage(0x5D);
        break;

    case UI::SCENE_CANNOT_ACCESS_SYSTEM_MEMORY:
        scene->buildPage(0x05);
        scene->buildPage(0x5D);
        break;

    case UI::SCENE_CANNOT_ACCESS_MII_DATA:
        scene->buildPage(0x06);
        scene->buildPage(0x5D);
        break;

    case UI::SCENE_ESRB_NOTICE:
        scene->buildPage(0x01);
        break;

    case UI::SCENE_RECOMMEND_60HZ_1:
        scene->buildPage(0x02);
        break;

    case UI::SCENE_RECOMMEND_60HZ_2:
        scene->buildPage(0x02);
        break;

    case UI::SCENE_GRAND_PRIX_PANORAMA:
        scene->buildPage(0x07);
        break;

    case UI::SCENE_VS_RACE_PANORAMA:
        scene->buildPage(0x08);
        break;

    case UI::SCENE_BALLOON_BATTLE_PANORAMA:
        scene->buildPage(0x09);
        break;

    case UI::SCENE_MISSION_BOSS_PANORAMA:
        scene->buildPage(0x0A);
        break;

    case UI::SCENE_TOURNAMENT_BOSS_PANORAMA:
        scene->buildPage(0x0B);
        break;

    case UI::SCENE_GRAND_PRIX_GAMEPLAY:
        scene->buildPage(0x0C);
        scene->buildPage(0x17);
        scene->buildPage(0x20);
        scene->buildPage(0x2C);
        scene->buildPage(0x2F);
        scene->buildPage(0x30);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_TIME_TRIAL_GAMEPLAY:
        scene->buildPage(0x0D);
        scene->buildPage(0x19);
        scene->buildPage(0x21);
        scene->buildPage(0x29);
        scene->buildPage(0x2B);
        scene->buildPage(0x2D);
        scene->buildPage(0x2E);
        scene->buildPage(0x3A);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_1P_VS_RACE_GAMEPLAY:
        scene->buildPage(0x0E);
        scene->buildPage(0x18);
        scene->buildPage(0x22);
        scene->buildPage(0x2F);
        scene->buildPage(0x30);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_2P_VS_RACE_GAMEPLAY:
        scene->buildPage(0x0F);
        scene->buildPage(0x18);
        scene->buildPage(0x22);
        scene->buildPage(0x2C);
        scene->buildPage(0x2F);
        scene->buildPage(0x30);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_3P_VS_RACE_GAMEPLAY:
        scene->buildPage(0x10);
        scene->buildPage(0x18);
        scene->buildPage(0x22);
        scene->buildPage(0x2C);
        scene->buildPage(0x2F);
        scene->buildPage(0x30);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_4P_VS_RACE_GAMEPLAY:
        scene->buildPage(0x11);
        scene->buildPage(0x18);
        scene->buildPage(0x22);
        scene->buildPage(0x2C);
        scene->buildPage(0x2F);
        scene->buildPage(0x30);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_1P_TEAM_VS_RACE_GAMEPLAY:
        scene->buildPage(0x0E);
        scene->buildPage(0x18);
        scene->buildPage(0x22);
        scene->buildPage(0x2F);
        scene->buildPage(0x32);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_2P_TEAM_VS_RACE_GAMEPLAY:
        scene->buildPage(0x0F);
        scene->buildPage(0x18);
        scene->buildPage(0x22);
        scene->buildPage(0x2C);
        scene->buildPage(0x2F);
        scene->buildPage(0x32);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_3P_TEAM_VS_RACE_GAMEPLAY:
        scene->buildPage(0x10);
        scene->buildPage(0x18);
        scene->buildPage(0x22);
        scene->buildPage(0x2C);
        scene->buildPage(0x2F);
        scene->buildPage(0x32);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_4P_TEAM_VS_RACE_GAMEPLAY:
        scene->buildPage(0x11);
        scene->buildPage(0x18);
        scene->buildPage(0x22);
        scene->buildPage(0x2C);
        scene->buildPage(0x2F);
        scene->buildPage(0x32);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_1P_BATTLE_GAMEPLAY:
        scene->buildPage(0x12);
        scene->buildPage(0x1A);
        scene->buildPage(0x23);
        scene->buildPage(0x24);
        scene->buildPage(0x33);
        scene->buildPage(0x34);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_2P_BATTLE_GAMEPLAY:
        scene->buildPage(0x13);
        scene->buildPage(0x1A);
        scene->buildPage(0x23);
        scene->buildPage(0x24);
        scene->buildPage(0x2C);
        scene->buildPage(0x33);
        scene->buildPage(0x34);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_3P_BATTLE_GAMEPLAY:
        scene->buildPage(0x14);
        scene->buildPage(0x1A);
        scene->buildPage(0x23);
        scene->buildPage(0x24);
        scene->buildPage(0x2C);
        scene->buildPage(0x33);
        scene->buildPage(0x34);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_4P_BATTLE_GAMEPLAY:
        scene->buildPage(0x15);
        scene->buildPage(0x1A);
        scene->buildPage(0x23);
        scene->buildPage(0x24);
        scene->buildPage(0x2C);
        scene->buildPage(0x33);
        scene->buildPage(0x34);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_MISSION_MODE_GAMEPLAY:
        scene->buildPage(0x16);
        scene->buildPage(0x1B);
        scene->buildPage(0x25);
        scene->buildPage(0x2C);
        scene->buildPage(0x3A);
        break;

    // Patched
    case UI::SCENE_TOURNAMENT_GAMEPLAY:
        SaveManagerPage::build(scene);
        if (isTournamentReplay())
            buildTournamentReplayPages(scene);
        else
            buildTournamentPages(scene);
        break;

    case UI::SCENE_GRAND_PRIX_REPLAY:
        scene->buildPage(0x2C);
        scene->buildPage(0x36);
        scene->buildPage(0x38);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_TIME_TRIAL_REPLAY:
        scene->buildPage(0x21);
        scene->buildPage(0x2B);
        scene->buildPage(0x37);
        scene->buildPage(0x39);
        scene->buildPage(0x3A);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_GHOST_RACE_GAMEPLAY_1:
        scene->buildPage(0x0D);
        scene->buildPage(0x1C);
        scene->buildPage(0x1D);
        scene->buildPage(0x1E);
        scene->buildPage(0x27);
        scene->buildPage(0x28);
        scene->buildPage(0x2C);
        scene->buildPage(0x2D);
        scene->buildPage(0x2E);
        scene->buildPage(0x3A);
        break;

    case UI::SCENE_GHOST_RACE_GAMEPLAY_2:
        scene->buildPage(0x0D);
        scene->buildPage(0x1C);
        scene->buildPage(0x1D);
        scene->buildPage(0x1E);
        scene->buildPage(0x27);
        scene->buildPage(0x28);
        scene->buildPage(0x2C);
        scene->buildPage(0x2D);
        scene->buildPage(0x2E);
        scene->buildPage(0x3A);
        scene->buildPage(0x88);
        break;

    case UI::SCENE_WATCH_GHOST_FROM_CHANNEL:
        scene->buildPage(0x1F);
        scene->buildPage(0x2C);
        scene->buildPage(0x37);
        scene->buildPage(0x3A);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_WATCH_GHOST_FROM_DOWNLOADS:
        scene->buildPage(0x1F);
        scene->buildPage(0x2C);
        scene->buildPage(0x37);
        scene->buildPage(0x3A);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_WATCH_GHOST_FROM_MENU:
        scene->buildPage(0x1F);
        scene->buildPage(0x2C);
        scene->buildPage(0x37);
        scene->buildPage(0x3A);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_GRAND_PRIX_AWARD:
        scene->buildPage(0x3B);
        scene->buildPage(0x3C);
        break;

    case UI::SCENE_VS_RACE_AWARD:
        scene->buildPage(0x3B);
        scene->buildPage(0x3C);
        break;

    case UI::SCENE_AWARD_37:
        scene->buildPage(0x3B);
        scene->buildPage(0x3C);
        break;

    case UI::SCENE_AWARD_38:
        scene->buildPage(0x3B);
        scene->buildPage(0x3C);
        break;

    case UI::SCENE_ENDING_NORMAL_A:
        scene->buildPage(0x3D);
        break;

    case UI::SCENE_ENDING_TRUE_A:
        scene->buildPage(0x3D);
        break;

    case UI::SCENE_ENDING_NORMAL_B:
        scene->buildPage(0x3D);
        scene->buildPage(0x3E);
        break;

    case UI::SCENE_ENDING_TRUE_B:
        scene->buildPage(0x3D);
        scene->buildPage(0x3E);
        break;

    case UI::SCENE_CONGRATULATIONS:
        scene->buildPage(0x3F);
        scene->buildPage(0x4F);
        scene->buildPage(0x51);
        scene->buildPage(0x53);
        scene->buildPage(0x7F);
        break;

    case UI::SCENE_CONGRATULATIONS_COMPLETE:
        scene->buildPage(0x3F);
        scene->buildPage(0x4F);
        scene->buildPage(0x51);
        scene->buildPage(0x53);
        scene->buildPage(0x7F);
        break;

    // Patched
    case UI::SCENE_MAIN_MENU_FROM_BOOT:
    case UI::SCENE_MAIN_MENU_FROM_RESET:
    case UI::SCENE_MAIN_MENU_FROM_MENU:
    case UI::SCENE_MAIN_MENU_FROM_NEW_LICENSE:
    case UI::SCENE_MAIN_MENU_FROM_LICENSE_43:
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0x65);
        {
            UI::TitleScreenPage* page = new UI::TitleScreenPage();
            page->hideBackground(true);
            scene->setPage(0x57, page);
            page->init(0x57);
        }
        break;

    case UI::SCENE_DEMO:
        scene->buildPage(0x3A);
        scene->buildPage(0x5F);
        break;

    case UI::SCENE_MII_SELECT_1:
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5D);
        scene->buildPage(0x5E);
        scene->buildPage(0x60);
        scene->buildPage(0x66);
        break;

    case UI::SCENE_MII_SELECT_2:
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5D);
        scene->buildPage(0x5E);
        scene->buildPage(0x60);
        scene->buildPage(0x66);
        break;

    case UI::SCENE_LICENSE_SETTINGS:
        scene->buildPage(0x4E);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5D);
        scene->buildPage(0x5E);
        scene->buildPage(0x60);
        scene->buildPage(0x66);
        scene->buildPage(0x67);
        scene->buildPage(0x68);
        scene->buildPage(0xCE);
        scene->buildPage(0xCF);
        scene->buildPage(0xD0);
        scene->buildPage(0xD1);
        scene->buildPage(0xD2);
        break;

    case UI::SCENE_SINGLE_PLAYER_FROM_MENU:
        scene->buildPage(0x4B);
        scene->buildPage(0x4D);
        scene->buildPage(0x4F);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x53);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x69);
        scene->buildPage(0x6A);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x6E);
        scene->buildPage(0x6F);
        scene->buildPage(0x70);
        scene->buildPage(0x71);
        scene->buildPage(0x72);
        scene->buildPage(0x73);
        scene->buildPage(0x74);
        scene->buildPage(0x75);
        scene->buildPage(0x76);
        scene->buildPage(0x77);
        scene->buildPage(0x78);
        scene->buildPage(0x79);
        scene->buildPage(0x7F);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_SINGLE_PLAYER_TT_CHANGE_CHARA:
        scene->buildPage(0x4B);
        scene->buildPage(0x4D);
        scene->buildPage(0x4F);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x53);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x69);
        scene->buildPage(0x6A);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x6E);
        scene->buildPage(0x6F);
        scene->buildPage(0x70);
        scene->buildPage(0x71);
        scene->buildPage(0x72);
        scene->buildPage(0x73);
        scene->buildPage(0x74);
        scene->buildPage(0x75);
        scene->buildPage(0x76);
        scene->buildPage(0x77);
        scene->buildPage(0x78);
        scene->buildPage(0x79);
        scene->buildPage(0x7F);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_SINGLE_PLAYER_TT_CHANGE_COURSE:
        scene->buildPage(0x4B);
        scene->buildPage(0x4D);
        scene->buildPage(0x4F);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x53);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x69);
        scene->buildPage(0x6A);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x6E);
        scene->buildPage(0x6F);
        scene->buildPage(0x70);
        scene->buildPage(0x71);
        scene->buildPage(0x72);
        scene->buildPage(0x73);
        scene->buildPage(0x74);
        scene->buildPage(0x75);
        scene->buildPage(0x76);
        scene->buildPage(0x77);
        scene->buildPage(0x78);
        scene->buildPage(0x79);
        scene->buildPage(0x7F);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_SINGLE_PLAYER_VS_NEXT_RACE:
        scene->buildPage(0x4B);
        scene->buildPage(0x4E);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x53);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x6E);
        scene->buildPage(0x6F);
        scene->buildPage(0x7F);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_SINGLE_PLAYER_BT_NEXT_BATTLE:
        scene->buildPage(0x4B);
        scene->buildPage(0x4E);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x53);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x78);
        scene->buildPage(0x79);
        scene->buildPage(0x7F);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_SINGLE_PLAYER_MR_CHOOSE_MISSION:
        scene->buildPage(0x4B);
        scene->buildPage(0x4D);
        scene->buildPage(0x4F);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x53);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x69);
        scene->buildPage(0x6A);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x6E);
        scene->buildPage(0x6F);
        scene->buildPage(0x70);
        scene->buildPage(0x71);
        scene->buildPage(0x72);
        scene->buildPage(0x73);
        scene->buildPage(0x74);
        scene->buildPage(0x75);
        scene->buildPage(0x76);
        scene->buildPage(0x77);
        scene->buildPage(0x78);
        scene->buildPage(0x79);
        scene->buildPage(0x7F);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_SINGLE_PLAYER_CHAN_RACE_GHOST:
        scene->buildPage(0x4B);
        scene->buildPage(0x4D);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x7F);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_SINGLE_PLAYER_LB_RACE_GHOST:
        scene->buildPage(0x4B);
        scene->buildPage(0x4D);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x7F);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_SINGLE_PLAYER_LIST_RACE_GHOST:
        scene->buildPage(0x4B);
        scene->buildPage(0x4D);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x7F);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_SEND_GHOST_TO_FRIEND:
        scene->buildPage(0x4F);
        scene->buildPage(0x51);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0xA7);
        scene->buildPage(0xB6);
        break;

    case UI::SCENE_RACE_GHOST_FROM_CHAN_BOOT:
        scene->buildPage(0x4F);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0xA7);
        scene->buildPage(0xB1);
        scene->buildPage(0xB2);
        break;

    case UI::SCENE_WATCH_REPLAY_FROM_CHAN_BOOT:
        scene->buildPage(0x4F);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0xA7);
        scene->buildPage(0xB1);
        scene->buildPage(0xB2);
        break;

    case UI::SCENE_LOCAL_MULTIPLAYER:
        scene->buildPage(0x4B);
        scene->buildPage(0x4C);
        scene->buildPage(0x4D);
        scene->buildPage(0x52);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x60);
        scene->buildPage(0x61);
        scene->buildPage(0x62);
        scene->buildPage(0x63);
        scene->buildPage(0x64);
        scene->buildPage(0x6B);
        scene->buildPage(0x6E);
        scene->buildPage(0x6F);
        scene->buildPage(0x72);
        scene->buildPage(0x73);
        scene->buildPage(0x74);
        scene->buildPage(0x75);
        scene->buildPage(0x77);
        scene->buildPage(0x78);
        scene->buildPage(0x79);
        scene->buildPage(0x7F);
        scene->buildPage(0x80);
        scene->buildPage(0x81);
        scene->buildPage(0x82);
        scene->buildPage(0x83);
        break;

    case UI::SCENE_1P_WIFI:
        scene->buildPage(0x4C);
        scene->buildPage(0x4D);
        scene->buildPage(0x4E);
        scene->buildPage(0x4F);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x76);
        scene->buildPage(0x7F);
        scene->buildPage(0x84);
        scene->buildPage(0x85);
        scene->buildPage(0x86);
        scene->buildPage(0x87);
        scene->buildPage(0x88);
        scene->buildPage(0x89);
        scene->buildPage(0x8B);
        scene->buildPage(0x8C);
        scene->buildPage(0x8D);
        scene->buildPage(0x8F);
        scene->buildPage(0x95);
        scene->buildPage(0x96);
        scene->buildPage(0x97);
        scene->buildPage(0x98);
        scene->buildPage(0x99);
        scene->buildPage(0x9B);
        scene->buildPage(0x9C);
        scene->buildPage(0x9D);
        scene->buildPage(0x9E);
        scene->buildPage(0xA5);
        scene->buildPage(0xA6);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_1P_WIFI_GLOBE_DISCONNECT:
        scene->buildPage(0x4C);
        scene->buildPage(0x4D);
        scene->buildPage(0x4E);
        scene->buildPage(0x4F);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x76);
        scene->buildPage(0x7F);
        scene->buildPage(0x84);
        scene->buildPage(0x85);
        scene->buildPage(0x86);
        scene->buildPage(0x87);
        scene->buildPage(0x88);
        scene->buildPage(0x89);
        scene->buildPage(0x8B);
        scene->buildPage(0x8C);
        scene->buildPage(0x8D);
        scene->buildPage(0x8F);
        scene->buildPage(0x95);
        scene->buildPage(0x96);
        scene->buildPage(0x97);
        scene->buildPage(0x98);
        scene->buildPage(0x99);
        scene->buildPage(0x9B);
        scene->buildPage(0x9C);
        scene->buildPage(0x9D);
        scene->buildPage(0x9E);
        scene->buildPage(0xA5);
        scene->buildPage(0xA6);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_1P_WIFI_FROM_FIND_FRIEND:
        scene->buildPage(0x4C);
        scene->buildPage(0x4D);
        scene->buildPage(0x4E);
        scene->buildPage(0x4F);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x76);
        scene->buildPage(0x7F);
        scene->buildPage(0x84);
        scene->buildPage(0x85);
        scene->buildPage(0x86);
        scene->buildPage(0x87);
        scene->buildPage(0x88);
        scene->buildPage(0x89);
        scene->buildPage(0x8B);
        scene->buildPage(0x8C);
        scene->buildPage(0x8D);
        scene->buildPage(0x8F);
        scene->buildPage(0x95);
        scene->buildPage(0x96);
        scene->buildPage(0x97);
        scene->buildPage(0x98);
        scene->buildPage(0x99);
        scene->buildPage(0x9B);
        scene->buildPage(0x9C);
        scene->buildPage(0x9D);
        scene->buildPage(0x9E);
        scene->buildPage(0xA5);
        scene->buildPage(0xA6);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_1P_WIFI_VS_VOTING:
        scene->buildPage(0x4E);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x6E);
        scene->buildPage(0x6F);
        scene->buildPage(0x7F);
        scene->buildPage(0x88);
        scene->buildPage(0x90);
        scene->buildPage(0x91);
        scene->buildPage(0x92);
        break;

    case UI::SCENE_1P_WIFI_BATTLE_VOTING:
        scene->buildPage(0x4E);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x78);
        scene->buildPage(0x79);
        scene->buildPage(0x7F);
        scene->buildPage(0x88);
        scene->buildPage(0x90);
        scene->buildPage(0x91);
        scene->buildPage(0x92);
        break;

    case UI::SCENE_2P_WIFI_SELECT_MII:
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0x60);
        scene->buildPage(0x61);
        scene->buildPage(0x62);
        scene->buildPage(0x63);
        scene->buildPage(0x64);
        scene->buildPage(0x8A);
        break;

    case UI::SCENE_2P_WIFI:
        scene->buildPage(0x4C);
        scene->buildPage(0x4D);
        scene->buildPage(0x4E);
        scene->buildPage(0x4F);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x76);
        scene->buildPage(0x7F);
        scene->buildPage(0x81);
        scene->buildPage(0x82);
        scene->buildPage(0x84);
        scene->buildPage(0x85);
        scene->buildPage(0x86);
        scene->buildPage(0x87);
        scene->buildPage(0x88);
        scene->buildPage(0x89);
        scene->buildPage(0x8B);
        scene->buildPage(0x8C);
        scene->buildPage(0x8D);
        scene->buildPage(0x8F);
        scene->buildPage(0x95);
        scene->buildPage(0x96);
        scene->buildPage(0x97);
        scene->buildPage(0x98);
        scene->buildPage(0x99);
        scene->buildPage(0x9B);
        scene->buildPage(0x9C);
        scene->buildPage(0x9D);
        scene->buildPage(0x9E);
        scene->buildPage(0xA5);
        scene->buildPage(0xA6);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_2P_WIFI_GLOBE_DISCONNECT:
        scene->buildPage(0x4C);
        scene->buildPage(0x4D);
        scene->buildPage(0x4E);
        scene->buildPage(0x4F);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x76);
        scene->buildPage(0x7F);
        scene->buildPage(0x81);
        scene->buildPage(0x82);
        scene->buildPage(0x84);
        scene->buildPage(0x85);
        scene->buildPage(0x86);
        scene->buildPage(0x87);
        scene->buildPage(0x88);
        scene->buildPage(0x89);
        scene->buildPage(0x8B);
        scene->buildPage(0x8C);
        scene->buildPage(0x8D);
        scene->buildPage(0x8F);
        scene->buildPage(0x95);
        scene->buildPage(0x96);
        scene->buildPage(0x97);
        scene->buildPage(0x98);
        scene->buildPage(0x99);
        scene->buildPage(0x9B);
        scene->buildPage(0x9C);
        scene->buildPage(0x9D);
        scene->buildPage(0x9E);
        scene->buildPage(0xA5);
        scene->buildPage(0xA6);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_UNKNOWN_5D:
        scene->buildPage(0x4C);
        scene->buildPage(0x4D);
        scene->buildPage(0x4E);
        scene->buildPage(0x4F);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x76);
        scene->buildPage(0x7F);
        scene->buildPage(0x81);
        scene->buildPage(0x82);
        scene->buildPage(0x84);
        scene->buildPage(0x85);
        scene->buildPage(0x86);
        scene->buildPage(0x87);
        scene->buildPage(0x88);
        scene->buildPage(0x89);
        scene->buildPage(0x8B);
        scene->buildPage(0x8C);
        scene->buildPage(0x8D);
        scene->buildPage(0x8F);
        scene->buildPage(0x95);
        scene->buildPage(0x96);
        scene->buildPage(0x97);
        scene->buildPage(0x98);
        scene->buildPage(0x99);
        scene->buildPage(0x9B);
        scene->buildPage(0x9C);
        scene->buildPage(0x9D);
        scene->buildPage(0x9E);
        scene->buildPage(0xA5);
        scene->buildPage(0xA6);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_2P_WIFI_VS_VOTING:
        scene->buildPage(0x4E);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x6E);
        scene->buildPage(0x6F);
        scene->buildPage(0x7F);
        scene->buildPage(0x88);
        scene->buildPage(0x90);
        scene->buildPage(0x91);
        scene->buildPage(0x92);
        break;

    case UI::SCENE_2P_WIFI_BATTLE_VOTING:
        scene->buildPage(0x4E);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x78);
        scene->buildPage(0x79);
        scene->buildPage(0x7F);
        scene->buildPage(0x88);
        scene->buildPage(0x90);
        scene->buildPage(0x91);
        scene->buildPage(0x92);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_ROOM_VS_VOTING:
        scene->buildPage(0x4E);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x6E);
        scene->buildPage(0x6F);
        scene->buildPage(0x7F);
        scene->buildPage(0x88);
        scene->buildPage(0x90);
        scene->buildPage(0x91);
        scene->buildPage(0x92);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_ROOM_TEAM_VS_VOTING:
        scene->buildPage(0x4E);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x6E);
        scene->buildPage(0x6F);
        scene->buildPage(0x7F);
        scene->buildPage(0x88);
        scene->buildPage(0x90);
        scene->buildPage(0x91);
        scene->buildPage(0x92);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_ROOM_BALLOON_VOTING:
        scene->buildPage(0x4E);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x78);
        scene->buildPage(0x79);
        scene->buildPage(0x7F);
        scene->buildPage(0x88);
        scene->buildPage(0x90);
        scene->buildPage(0x91);
        scene->buildPage(0x92);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_ROOM_COIN_VOTING:
        scene->buildPage(0x4E);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x78);
        scene->buildPage(0x79);
        scene->buildPage(0x7F);
        scene->buildPage(0x88);
        scene->buildPage(0x90);
        scene->buildPage(0x91);
        scene->buildPage(0x92);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_ROOM_VS_VOTING:
        scene->buildPage(0x4E);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x6E);
        scene->buildPage(0x6F);
        scene->buildPage(0x7F);
        scene->buildPage(0x88);
        scene->buildPage(0x90);
        scene->buildPage(0x91);
        scene->buildPage(0x92);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_ROOM_TEAM_VS_VOTING:
        scene->buildPage(0x4E);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x6E);
        scene->buildPage(0x6F);
        scene->buildPage(0x7F);
        scene->buildPage(0x88);
        scene->buildPage(0x90);
        scene->buildPage(0x91);
        scene->buildPage(0x92);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_ROOM_BALLOON_VOTING:
        scene->buildPage(0x4E);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x78);
        scene->buildPage(0x79);
        scene->buildPage(0x7F);
        scene->buildPage(0x88);
        scene->buildPage(0x90);
        scene->buildPage(0x91);
        scene->buildPage(0x92);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_ROOM_COIN_VOTING:
        scene->buildPage(0x4E);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x5C);
        scene->buildPage(0x5E);
        scene->buildPage(0x78);
        scene->buildPage(0x79);
        scene->buildPage(0x7F);
        scene->buildPage(0x88);
        scene->buildPage(0x90);
        scene->buildPage(0x91);
        scene->buildPage(0x92);
        break;

    case UI::SCENE_1P_WIFI_VS_GAMEPLAY:
        scene->buildPage(0x31);
        scene->buildPage(0x3A);
        scene->buildPage(0x40);
        scene->buildPage(0x45);
        scene->buildPage(0x46);
        scene->buildPage(0x47);
        scene->buildPage(0x48);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_2P_WIFI_VS_GAMEPLAY:
        scene->buildPage(0x31);
        scene->buildPage(0x3A);
        scene->buildPage(0x41);
        scene->buildPage(0x45);
        scene->buildPage(0x46);
        scene->buildPage(0x47);
        scene->buildPage(0x48);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_1P_WIFI_VS_LIVE_VIEW:
        scene->buildPage(0x3A);
        scene->buildPage(0x48);
        scene->buildPage(0x49);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x93);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_2P_WIFI_VS_LIVE_VIEW:
        scene->buildPage(0x3A);
        scene->buildPage(0x48);
        scene->buildPage(0x49);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x93);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_1P_WIFI_BT_GAMEPLAY:
        scene->buildPage(0x12);
        scene->buildPage(0x31);
        scene->buildPage(0x33);
        scene->buildPage(0x3A);
        scene->buildPage(0x45);
        scene->buildPage(0x46);
        scene->buildPage(0x47);
        scene->buildPage(0x48);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_2P_WIFI_BT_GAMEPLAY:
        scene->buildPage(0x13);
        scene->buildPage(0x31);
        scene->buildPage(0x33);
        scene->buildPage(0x3A);
        scene->buildPage(0x45);
        scene->buildPage(0x46);
        scene->buildPage(0x47);
        scene->buildPage(0x48);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_1P_WIFI_BT_LIVE_VIEW:
        scene->buildPage(0x33);
        scene->buildPage(0x3A);
        scene->buildPage(0x48);
        scene->buildPage(0x4A);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x93);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_2P_WIFI_BT_LIVE_VIEW:
        scene->buildPage(0x33);
        scene->buildPage(0x3A);
        scene->buildPage(0x48);
        scene->buildPage(0x4A);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x93);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_VS_GAMEPLAY:
        scene->buildPage(0x2F);
        scene->buildPage(0x30);
        scene->buildPage(0x3A);
        scene->buildPage(0x42);
        scene->buildPage(0x44);
        scene->buildPage(0x48);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_TEAM_VS_GAMEPLAY:
        scene->buildPage(0x2F);
        scene->buildPage(0x32);
        scene->buildPage(0x3A);
        scene->buildPage(0x42);
        scene->buildPage(0x44);
        scene->buildPage(0x48);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_BALLOON_BT_GAMEPLAY:
        scene->buildPage(0x12);
        scene->buildPage(0x33);
        scene->buildPage(0x34);
        scene->buildPage(0x3A);
        scene->buildPage(0x44);
        scene->buildPage(0x48);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_COIN_BT_GAMEPLAY:
        scene->buildPage(0x12);
        scene->buildPage(0x33);
        scene->buildPage(0x34);
        scene->buildPage(0x3A);
        scene->buildPage(0x44);
        scene->buildPage(0x48);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_VS_GAMEPLAY:
        scene->buildPage(0x2F);
        scene->buildPage(0x30);
        scene->buildPage(0x3A);
        scene->buildPage(0x43);
        scene->buildPage(0x44);
        scene->buildPage(0x48);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_TEAM_VS_GAMEPLAY:
        scene->buildPage(0x2F);
        scene->buildPage(0x32);
        scene->buildPage(0x3A);
        scene->buildPage(0x43);
        scene->buildPage(0x44);
        scene->buildPage(0x48);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_BALLOON_BT_GAMEPLAY:
        scene->buildPage(0x13);
        scene->buildPage(0x33);
        scene->buildPage(0x34);
        scene->buildPage(0x3A);
        scene->buildPage(0x44);
        scene->buildPage(0x48);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_COIN_BT_GAMEPLAY:
        scene->buildPage(0x13);
        scene->buildPage(0x33);
        scene->buildPage(0x34);
        scene->buildPage(0x3A);
        scene->buildPage(0x44);
        scene->buildPage(0x48);
        scene->buildPage(0x51);
        scene->buildPage(0x88);
        scene->buildPage(0x94);
        break;

    case UI::SCENE_WIFI_DISCONNECT_ERROR:
        scene->buildPage(0x5D);
        scene->buildPage(0x89);
        break;

    case UI::SCENE_WIFI_DISCONNECT_GENERAL:
        scene->buildPage(0x5D);
        scene->buildPage(0x89);
        break;

    case UI::SCENE_CHANNEL_FROM_MENU:
        scene->buildPage(0x4D);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0xA2);
        scene->buildPage(0xA3);
        scene->buildPage(0xA4);
        break;

    case UI::SCENE_CHANNEL_FROM_CHECK_RANKINGS:
        scene->buildPage(0x4D);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0xA2);
        scene->buildPage(0xA3);
        scene->buildPage(0xA4);
        break;

    case UI::SCENE_CHANNEL_FROM_DOWNLOADS:
        scene->buildPage(0x4D);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0xA2);
        scene->buildPage(0xA3);
        scene->buildPage(0xA4);
        break;

    case UI::SCENE_TIME_TRIAL_LEADERBOARDS:
        scene->buildPage(0x4E);
        scene->buildPage(0x4F);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x6E);
        scene->buildPage(0x6F);
        scene->buildPage(0x84);
        scene->buildPage(0x85);
        scene->buildPage(0x86);
        scene->buildPage(0x88);
        scene->buildPage(0x89);
        scene->buildPage(0x95);
        scene->buildPage(0xA7);
        scene->buildPage(0xA8);
        scene->buildPage(0xAA);
        scene->buildPage(0xAB);
        scene->buildPage(0xAC);
        scene->buildPage(0xAD);
        scene->buildPage(0xAE);
        scene->buildPage(0xAF);
        break;

    case UI::SCENE_TOURNAMENT_LEADERBOARDS:
        scene->buildPage(0x4E);
        scene->buildPage(0x4F);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x84);
        scene->buildPage(0x85);
        scene->buildPage(0x86);
        scene->buildPage(0x88);
        scene->buildPage(0x89);
        scene->buildPage(0x95);
        scene->buildPage(0xA9);
        scene->buildPage(0xAA);
        scene->buildPage(0xAB);
        scene->buildPage(0xAE);
        scene->buildPage(0xAF);
        scene->buildPage(0xB0);
        break;

    case UI::SCENE_GHOST_RACE_WITH_DATA:
        scene->buildPage(0x4B);
        scene->buildPage(0x4D);
        scene->buildPage(0x51);
        scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x7F);
        scene->buildPage(0x9F);
        scene->buildPage(0xA0);
        scene->buildPage(0xA1);
        break;

    case UI::SCENE_GHOST_RACE_WITHOUT_DATA:
        scene->buildPage(0x4B);
        scene->buildPage(0x4D);
        scene->buildPage(0x4E);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x7F);
        scene->buildPage(0x84);
        scene->buildPage(0x85);
        scene->buildPage(0x86);
        scene->buildPage(0x88);
        scene->buildPage(0x89);
        scene->buildPage(0x9F);
        scene->buildPage(0xA0);
        scene->buildPage(0xA1);
        break;

    case UI::SCENE_GHOST_RACE_NEXT_RACE:
        scene->buildPage(0x4B);
        scene->buildPage(0x4D);
        scene->buildPage(0x4E);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x7F);
        scene->buildPage(0x84);
        scene->buildPage(0x85);
        scene->buildPage(0x86);
        scene->buildPage(0x88);
        scene->buildPage(0x89);
        scene->buildPage(0xA0);
        scene->buildPage(0xA1);
        break;

    case UI::SCENE_DOWNLOADED_GHOST_DATA:
        scene->buildPage(0x4D);
        scene->buildPage(0x4F);
        scene->buildPage(0x51);
        scene->buildPage(0x5E);
        scene->buildPage(0xA7);
        scene->buildPage(0xB3);
        scene->buildPage(0xB4);
        scene->buildPage(0xB5);
        break;

    case UI::SCENE_FRIENDS_LIST_1:
        scene->buildPage(0x4C);
        scene->buildPage(0x4D);
        scene->buildPage(0x4E);
        scene->buildPage(0x4F);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x76);
        scene->buildPage(0x7F);
        scene->buildPage(0x84);
        scene->buildPage(0x85);
        scene->buildPage(0x86);
        scene->buildPage(0x87);
        scene->buildPage(0x88);
        scene->buildPage(0x89);
        scene->buildPage(0x8E);
        scene->buildPage(0x8F);
        scene->buildPage(0x95);
        scene->buildPage(0x96);
        scene->buildPage(0x97);
        scene->buildPage(0x98);
        scene->buildPage(0x99);
        scene->buildPage(0x9B);
        scene->buildPage(0x9C);
        scene->buildPage(0x9D);
        scene->buildPage(0x9E);
        scene->buildPage(0xA5);
        scene->buildPage(0xA6);
        scene->buildPage(0xA7);
        break;

    case UI::SCENE_FRIENDS_LIST_2:
        scene->buildPage(0x4C);
        scene->buildPage(0x4D);
        scene->buildPage(0x4E);
        scene->buildPage(0x4F);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x76);
        scene->buildPage(0x7F);
        scene->buildPage(0x84);
        scene->buildPage(0x85);
        scene->buildPage(0x86);
        scene->buildPage(0x87);
        scene->buildPage(0x88);
        scene->buildPage(0x89);
        scene->buildPage(0x8E);
        scene->buildPage(0x8F);
        scene->buildPage(0x95);
        scene->buildPage(0x96);
        scene->buildPage(0x97);
        scene->buildPage(0x98);
        scene->buildPage(0x99);
        scene->buildPage(0x9A);
        scene->buildPage(0x9B);
        scene->buildPage(0x9C);
        scene->buildPage(0x9D);
        scene->buildPage(0x9E);
        scene->buildPage(0xA5);
        scene->buildPage(0xA6);
        scene->buildPage(0xA7);
        break;

    // Patched
    case UI::SCENE_TOURNAMENT:
    case UI::SCENE_TOURNAMENT_CHANGE_CHARA:
        SaveManagerPage::build(scene);
        scene->buildPage(0x4B);
        scene->buildPage(0x4D);
        scene->buildPage(0x51);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x7F);
        scene->buildPage(0xB7);
        scene->buildPage(0xB8);
        scene->buildPage(0xBB);
        {
            SelectionPage* page = new SelectionPage();
            scene->setPage(0x8C, page);
            page->init(0x8C);
        }
        break;

    case UI::SCENE_TOURNAMENT_SUBMIT_RECORD:
        scene->buildPage(0x4E);
        scene->buildPage(0x4F);
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x5E);
        scene->buildPage(0x84);
        scene->buildPage(0x85);
        scene->buildPage(0x86);
        scene->buildPage(0x88);
        scene->buildPage(0x89);
        scene->buildPage(0xB9);
        break;

    // Patched
    case UI::SCENE_TOURNAMENT_WII_WHEEL_ONLY:
    case UI::SCENE_TOURNAMENT_WII_WHEEL_ONLY_BOSSES:
        scene->buildPage(0x5B);
        scene->buildPage(0xBA);
        scene->buildPage(0x4E);
        {
            ForcedHandleBypassPage* page = new ForcedHandleBypassPage();
            scene->setPage(0x87, page);
            page->init(0x87);
        }
        break;

    case UI::SCENE_INVITE_FRIENDS_FROM_MSG_BOARD:
        scene->buildPage(0x4F);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0xBD);
        scene->buildPage(0xBE);
        scene->buildPage(0xBF);
        break;

    case UI::SCENE_DOWNLOAD_LATEST_DATA:
        scene->buildPage(0x50);
        scene->buildPage(0x51);
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0xBC);
        break;

    // Patched
    case UI::SCENE_OPTIONS:
    case UI::SCENE_INSTALL_CHANNEL:
        SaveManagerPage::build(scene);
        scene->buildPage(0x4D);
        scene->buildPage(0x4E);
        scene->buildPage(0x5D);
        scene->buildPage(0xC2);
        scene->buildPage(0xC3);
        scene->buildPage(0xC4);
        scene->buildPage(0xC6);
        scene->buildPage(0xC7);
        scene->buildPage(0xC8);
        scene->buildPage(0xC9);
        scene->buildPage(0xCC);
        {
            SettingsPage* page = new SettingsPage();
            scene->setPage(0xC0, page);
            page->init(0xC0);
        }
        {
            SettingsGhostDataPage* page = new SettingsGhostDataPage();
            scene->setPage(SettingsGhostDataPage::s_pageId, page);
            page->init(SettingsGhostDataPage::s_pageId);
        }
        break;

    case UI::SCENE_CHOOSE_REGION:
        scene->buildPage(0x5D);
        scene->buildPage(0xC5);
        scene->buildPage(0xCC);
        break;

    case UI::SCENE_JOIN_MESSAGE_SERVICE:
        scene->buildPage(0x4E);
        scene->buildPage(0x5D);
        scene->buildPage(0xC2);
        scene->buildPage(0xC3);
        scene->buildPage(0xC6);
        scene->buildPage(0xC7);
        scene->buildPage(0xC8);
        scene->buildPage(0xC9);
        scene->buildPage(0xCC);
        break;

    case UI::SCENE_MSG_UNLOCK_PINK:
        scene->buildPage(0x5B);
        scene->buildPage(0x5E);
        scene->buildPage(0x7F);
        scene->buildPage(0xCD);
        break;

    case UI::SCENE_MSG_UNLOCK_ORANGE:
        scene->buildPage(0x5B);
        scene->buildPage(0x5E);
        scene->buildPage(0x7F);
        scene->buildPage(0xCD);
        break;

    case UI::SCENE_MSG_UNLOCK_BLUE:
        scene->buildPage(0x5B);
        scene->buildPage(0x5E);
        scene->buildPage(0x7F);
        scene->buildPage(0xCD);
        break;

    case UI::SCENE_MSG_UNLOCK_YELLOW:
        scene->buildPage(0x5B);
        scene->buildPage(0x5E);
        scene->buildPage(0x7F);
        scene->buildPage(0xCD);
        break;

    case UI::SCENE_BROKEN_MISSION_MODE_MENU:
        scene->buildPage(0x7A);
        scene->buildPage(0x7B);
        scene->buildPage(0x7C);
        scene->buildPage(0x7D);
        scene->buildPage(0x7E);
    }
}

void showBasePagesReplace(UI::UIPageManager* scene, int id)
{
    switch (id) {
    case UI::SCENE_TEST_6:
        scene->showPageOnTop(0x00);
        break;

    case UI::SCENE_TEST_7:
        scene->showPageOnTop(0x00);
        break;

    case UI::SCENE_TEST_8:
        scene->showPageOnTop(0x00);
        break;

    case UI::SCENE_TEST_9:
        scene->showPageOnTop(0x00);
        break;

    case UI::SCENE_TEST_A:
        scene->showPageOnTop(0x00);
        break;

    case UI::SCENE_TEST_B:
        scene->showPageOnTop(0x00);
        break;

    case UI::SCENE_TEST_C:
        scene->showPageOnTop(0x00);
        break;

    case UI::SCENE_TEST_D:
        scene->showPageOnTop(0x00);
        break;

    case UI::SCENE_TEST_E:
        scene->showPageOnTop(0x00);
        break;

    case UI::SCENE_TEST_F:
        scene->showPageOnTop(0x00);
        break;

    case UI::SCENE_CREATE_NEW_SAVE:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0x03);
        break;

    case UI::SCENE_CORRUPTED_SAVE:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0x03);
        break;

    case UI::SCENE_COUNTRY_CHANGED:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0x03);
        break;

    case UI::SCENE_GAME_CANNOT_BE_SAVED:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0x04);
        break;

    case UI::SCENE_CANNOT_ACCESS_SYSTEM_MEMORY:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0x05);
        break;

    case UI::SCENE_CANNOT_ACCESS_MII_DATA:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0x06);
        break;

    case UI::SCENE_ESRB_NOTICE:
        scene->showPageOnTop(0x01);
        break;

    case UI::SCENE_RECOMMEND_60HZ_1:
        scene->showPageOnTop(0x02);
        break;

    case UI::SCENE_RECOMMEND_60HZ_2:
        scene->showPageOnTop(0x02);
        break;

    case UI::SCENE_GRAND_PRIX_PANORAMA:
        scene->showPageOnTop(0x07);
        break;

    case UI::SCENE_VS_RACE_PANORAMA:
        scene->showPageOnTop(0x08);
        break;

    case UI::SCENE_BALLOON_BATTLE_PANORAMA:
        scene->showPageOnTop(0x09);
        break;

    case UI::SCENE_MISSION_BOSS_PANORAMA:
        scene->showPageOnTop(0x0A);
        break;

    case UI::SCENE_TOURNAMENT_BOSS_PANORAMA:
        scene->showPageOnTop(0x0B);
        break;

    case UI::SCENE_GRAND_PRIX_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x0C);
        break;

    case UI::SCENE_TIME_TRIAL_GAMEPLAY:
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x0D);
        break;

    case UI::SCENE_1P_VS_RACE_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x0E);
        break;

    case UI::SCENE_2P_VS_RACE_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x0F);
        break;

    case UI::SCENE_3P_VS_RACE_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x10);
        break;

    case UI::SCENE_4P_VS_RACE_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x11);
        break;

    case UI::SCENE_1P_TEAM_VS_RACE_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x0E);
        break;

    case UI::SCENE_2P_TEAM_VS_RACE_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x0F);
        break;

    case UI::SCENE_3P_TEAM_VS_RACE_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x10);
        break;

    case UI::SCENE_4P_TEAM_VS_RACE_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x11);
        break;

    case UI::SCENE_1P_BATTLE_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x12);
        break;

    case UI::SCENE_2P_BATTLE_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x13);
        break;

    case UI::SCENE_3P_BATTLE_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x14);
        break;

    case UI::SCENE_4P_BATTLE_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x15);
        break;

    case UI::SCENE_MISSION_MODE_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x16);
        break;

    case UI::SCENE_TOURNAMENT_GAMEPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x16);
        break;

    case UI::SCENE_GRAND_PRIX_REPLAY:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x36);
        break;

    case UI::SCENE_TIME_TRIAL_REPLAY:
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x37);
        break;

    case UI::SCENE_GHOST_RACE_GAMEPLAY_1:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x0D);
        break;

    case UI::SCENE_GHOST_RACE_GAMEPLAY_2:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x0D);
        break;

    case UI::SCENE_WATCH_GHOST_FROM_CHANNEL:
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x37);
        break;

    case UI::SCENE_WATCH_GHOST_FROM_DOWNLOADS:
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x37);
        break;

    case UI::SCENE_WATCH_GHOST_FROM_MENU:
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x37);
        break;

    case UI::SCENE_GRAND_PRIX_AWARD:
        scene->showPageOnTop(0x3B);
        break;

    case UI::SCENE_VS_RACE_AWARD:
        scene->showPageOnTop(0x3B);
        break;

    case UI::SCENE_AWARD_37:
        scene->showPageOnTop(0x3B);
        break;

    case UI::SCENE_AWARD_38:
        scene->showPageOnTop(0x3B);
        break;

    case UI::SCENE_ENDING_NORMAL_A:
        scene->showPageOnTop(0x3D);
        break;

    case UI::SCENE_ENDING_TRUE_A:
        scene->showPageOnTop(0x3D);
        break;

    case UI::SCENE_ENDING_NORMAL_B:
        scene->showPageOnTop(0x3E);
        scene->showPageOnTop(0x3D);
        break;

    case UI::SCENE_ENDING_TRUE_B:
        scene->showPageOnTop(0x3E);
        scene->showPageOnTop(0x3D);
        break;

    case UI::SCENE_CONGRATULATIONS:
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x3F);
        break;

    case UI::SCENE_CONGRATULATIONS_COMPLETE:
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x3F);
        break;

    // Patched
    case UI::SCENE_MAIN_MENU_FROM_BOOT:
    case UI::SCENE_MAIN_MENU_FROM_RESET:
    case UI::SCENE_MAIN_MENU_FROM_MENU:
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x57);
        break;

    // Patched
    case UI::SCENE_MAIN_MENU_FROM_NEW_LICENSE:
    case UI::SCENE_MAIN_MENU_FROM_LICENSE_43:
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x65);
        break;

    case UI::SCENE_DEMO:
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x5F);
        break;

    case UI::SCENE_MII_SELECT_1:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x60);
        break;

    case UI::SCENE_MII_SELECT_2:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x60);
        break;

    case UI::SCENE_LICENSE_SETTINGS:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x67);
        break;

    case UI::SCENE_SINGLE_PLAYER_FROM_MENU:
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x69);
        break;

    case UI::SCENE_SINGLE_PLAYER_TT_CHANGE_CHARA:
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x6B);
        break;

    case UI::SCENE_SINGLE_PLAYER_TT_CHANGE_COURSE:
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x6E);
        break;

    case UI::SCENE_SINGLE_PLAYER_VS_NEXT_RACE:
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x6E);
        break;

    case UI::SCENE_SINGLE_PLAYER_BT_NEXT_BATTLE:
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x78);
        break;

    case UI::SCENE_SINGLE_PLAYER_MR_CHOOSE_MISSION:
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x7F);
        break;

    case UI::SCENE_SINGLE_PLAYER_CHAN_RACE_GHOST:
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x6B);
        break;

    case UI::SCENE_SINGLE_PLAYER_LB_RACE_GHOST:
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x6B);
        break;

    case UI::SCENE_SINGLE_PLAYER_LIST_RACE_GHOST:
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x6B);
        break;

    case UI::SCENE_SEND_GHOST_TO_FRIEND:
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0xB6);
        break;

    case UI::SCENE_RACE_GHOST_FROM_CHAN_BOOT:
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0xB1);
        break;

    case UI::SCENE_WATCH_REPLAY_FROM_CHAN_BOOT:
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0xB1);
        break;

    case UI::SCENE_LOCAL_MULTIPLAYER:
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x61);
        break;

    case UI::SCENE_1P_WIFI:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x95);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x84);
        break;

    case UI::SCENE_1P_WIFI_GLOBE_DISCONNECT:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x95);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x9B);
        break;

    case UI::SCENE_1P_WIFI_FROM_FIND_FRIEND:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x95);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x96);
        break;

    case UI::SCENE_1P_WIFI_VS_VOTING:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x90);
        break;

    case UI::SCENE_1P_WIFI_BATTLE_VOTING:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x90);
        break;

    case UI::SCENE_2P_WIFI_SELECT_MII:
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x61);
        break;

    case UI::SCENE_2P_WIFI:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x95);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x84);
        break;

    case UI::SCENE_2P_WIFI_GLOBE_DISCONNECT:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x95);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x9B);
        break;

    case UI::SCENE_UNKNOWN_5D:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x95);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x96);
        break;

    case UI::SCENE_2P_WIFI_VS_VOTING:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x90);
        break;

    case UI::SCENE_2P_WIFI_BATTLE_VOTING:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x90);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_ROOM_VS_VOTING:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x90);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_ROOM_TEAM_VS_VOTING:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x90);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_ROOM_BALLOON_VOTING:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x90);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_ROOM_COIN_VOTING:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x90);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_ROOM_VS_VOTING:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x90);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_ROOM_TEAM_VS_VOTING:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x90);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_ROOM_BALLOON_VOTING:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x90);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_ROOM_COIN_VOTING:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5C);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x90);
        break;

    case UI::SCENE_1P_WIFI_VS_GAMEPLAY:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x40);
        break;

    case UI::SCENE_2P_WIFI_VS_GAMEPLAY:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x41);
        break;

    case UI::SCENE_1P_WIFI_VS_LIVE_VIEW:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x93);
        break;

    case UI::SCENE_2P_WIFI_VS_LIVE_VIEW:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x93);
        break;

    case UI::SCENE_1P_WIFI_BT_GAMEPLAY:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x12);
        break;

    case UI::SCENE_2P_WIFI_BT_GAMEPLAY:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x13);
        break;

    case UI::SCENE_1P_WIFI_BT_LIVE_VIEW:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x93);
        break;

    case UI::SCENE_2P_WIFI_BT_LIVE_VIEW:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x93);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_VS_GAMEPLAY:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x42);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_TEAM_VS_GAMEPLAY:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x42);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_BALLOON_BT_GAMEPLAY:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x12);
        break;

    case UI::SCENE_1P_WIFI_FRIEND_COIN_BT_GAMEPLAY:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x12);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_VS_GAMEPLAY:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x43);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_TEAM_VS_GAMEPLAY:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x43);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_BALLOON_BT_GAMEPLAY:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x13);
        break;

    case UI::SCENE_2P_WIFI_FRIEND_COIN_BT_GAMEPLAY:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x94);
        scene->showPageOnTop(0x3A);
        scene->showPageOnTop(0x13);
        break;

    case UI::SCENE_WIFI_DISCONNECT_ERROR:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0x89);
        break;

    case UI::SCENE_WIFI_DISCONNECT_GENERAL:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0x89);
        break;

    case UI::SCENE_CHANNEL_FROM_MENU:
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA2);
        break;

    case UI::SCENE_CHANNEL_FROM_CHECK_RANKINGS:
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA3);
        break;

    case UI::SCENE_CHANNEL_FROM_DOWNLOADS:
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA4);
        break;

    case UI::SCENE_TIME_TRIAL_LEADERBOARDS:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0xAA);
        scene->showPageOnTop(0xAB);
        scene->showPageOnTop(0x95);
        scene->showPageOnTop(0xA8);
        break;

    case UI::SCENE_TOURNAMENT_LEADERBOARDS:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0xAA);
        scene->showPageOnTop(0xAB);
        scene->showPageOnTop(0x95);
        scene->showPageOnTop(0xB0);
        break;

    case UI::SCENE_GHOST_RACE_WITH_DATA:
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x9F);
        break;

    case UI::SCENE_GHOST_RACE_WITHOUT_DATA:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x9F);
        break;

    case UI::SCENE_GHOST_RACE_NEXT_RACE:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x84);
        break;

    case UI::SCENE_DOWNLOADED_GHOST_DATA:
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0xB3);
        break;

    case UI::SCENE_FRIENDS_LIST_1:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x95);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x84);
        break;

    case UI::SCENE_FRIENDS_LIST_2:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0xA7);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x95);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x84);
        break;

    // Patched
    case UI::SCENE_TOURNAMENT:
        scene->showPageOnTop(0xBB);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x8C);
        break;

    case UI::SCENE_TOURNAMENT_CHANGE_CHARA:
        scene->showPageOnTop(0xBB);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0xB7);
        break;

    case UI::SCENE_TOURNAMENT_SUBMIT_RECORD:
        scene->showPageOnTop(0x88);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x84);
        break;

    case UI::SCENE_TOURNAMENT_WII_WHEEL_ONLY:
        scene->showPageOnTop(0x5B);
        scene->showPageOnTop(0xBA);
        break;

    case UI::SCENE_TOURNAMENT_WII_WHEEL_ONLY_BOSSES:
        scene->showPageOnTop(0x5B);
        scene->showPageOnTop(0xBA);
        break;

    case UI::SCENE_INVITE_FRIENDS_FROM_MSG_BOARD:
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xBD);
        break;

    case UI::SCENE_DOWNLOAD_LATEST_DATA:
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xBC);
        break;

    case UI::SCENE_OPTIONS:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0xCC);
        scene->showPageOnTop(0xC0);
        break;

    // Patched (used as Options from License Settings)
    case UI::SCENE_INSTALL_CHANNEL:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0xCC);
        scene->showPageOnTop(0xC0);
        break;

    case UI::SCENE_CHOOSE_REGION:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0xCC);
        scene->showPageOnTop(0xC5);
        break;

    case UI::SCENE_JOIN_MESSAGE_SERVICE:
        scene->showPageOnTop(0x5D);
        scene->showPageOnTop(0xCC);
        scene->showPageOnTop(0xC6);
        break;

    case UI::SCENE_MSG_UNLOCK_PINK:
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x5B);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xCD);
        break;

    case UI::SCENE_MSG_UNLOCK_ORANGE:
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x5B);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xCD);
        break;

    case UI::SCENE_MSG_UNLOCK_BLUE:
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x5B);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xCD);
        break;

    case UI::SCENE_MSG_UNLOCK_YELLOW:
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0x5B);
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0xCD);
    }
}

s32 patchLicenseSelectGetNextScene()
{
    return 0x85;
}

bool sceneHasBackModelReplace(int id)
{
    return false;
}

s32 sceneGetBGMReplace(int id)
{
    switch (id) {
    case UI::SCENE_GRAND_PRIX_PANORAMA:
        return Sound::STRM_O_CRS_IN_FAN;

    case UI::SCENE_BALLOON_BATTLE_PANORAMA:
    case UI::SCENE_MISSION_BOSS_PANORAMA:
    case UI::SCENE_TOURNAMENT_BOSS_PANORAMA:
        return Sound::STRM_O_B_CRS_IN_FAN;

    case UI::SCENE_GRAND_PRIX_GAMEPLAY:
        return Sound::STRM_O_START_FAN;

    case UI::SCENE_TIME_TRIAL_GAMEPLAY:
        return Sound::STRM_O_START2_FAN;

    case UI::SCENE_1P_VS_RACE_GAMEPLAY:
    case UI::SCENE_2P_VS_RACE_GAMEPLAY:
    case UI::SCENE_3P_VS_RACE_GAMEPLAY:
    case UI::SCENE_4P_VS_RACE_GAMEPLAY:
    case UI::SCENE_1P_TEAM_VS_RACE_GAMEPLAY:
    case UI::SCENE_2P_TEAM_VS_RACE_GAMEPLAY:
    case UI::SCENE_3P_TEAM_VS_RACE_GAMEPLAY:
    case UI::SCENE_4P_TEAM_VS_RACE_GAMEPLAY:
        return Sound::STRM_O_START_FAN;

    case UI::SCENE_1P_BATTLE_GAMEPLAY:
    case UI::SCENE_2P_BATTLE_GAMEPLAY:
    case UI::SCENE_3P_BATTLE_GAMEPLAY:
    case UI::SCENE_4P_BATTLE_GAMEPLAY:
    case UI::SCENE_MISSION_MODE_GAMEPLAY:
    case UI::SCENE_TOURNAMENT_GAMEPLAY:
        return Sound::STRM_O_START2_FAN;

    case UI::SCENE_MAIN_MENU_FROM_BOOT:
    case UI::SCENE_MAIN_MENU_FROM_RESET:
    case UI::SCENE_MAIN_MENU_FROM_MENU:
    case UI::SCENE_MAIN_MENU_FROM_NEW_LICENSE:
    case UI::SCENE_MAIN_MENU_FROM_LICENSE_43:
        return Sound::SEQ_O_SELECT_CH;

    case UI::SCENE_TOURNAMENT:
    case UI::SCENE_TOURNAMENT_CHANGE_CHARA:
        return Sound::SEQ_O_EARTH;

    case UI::SCENE_MII_SELECT_1:
    case UI::SCENE_MII_SELECT_2:
    case UI::SCENE_LICENSE_SETTINGS:
    case UI::SCENE_OPTIONS:
    case UI::SCENE_INSTALL_CHANNEL:
        return Sound::STRM_O_OPTION;
    default:
        return -1;
    }
}
s32 sceneGetBGMGroupReplace(int id)
{
    switch (id) {
    case UI::SCENE_MAIN_MENU_FROM_BOOT:
    case UI::SCENE_MAIN_MENU_FROM_RESET:
    case UI::SCENE_MAIN_MENU_FROM_MENU:
    case UI::SCENE_MAIN_MENU_FROM_NEW_LICENSE:
    case UI::SCENE_MAIN_MENU_FROM_LICENSE_43:
        return Sound::GRP_CH_MENU;

    case UI::SCENE_TOURNAMENT:
    case UI::SCENE_TOURNAMENT_CHANGE_CHARA:
        return Sound::GRP_CH_EARTH;

    case UI::SCENE_MII_SELECT_1:
    case UI::SCENE_MII_SELECT_2:
    case UI::SCENE_LICENSE_SETTINGS:
    case UI::SCENE_OPTIONS:
    case UI::SCENE_INSTALL_CHANNEL:
        return Sound::GRP_PRESENT;
    default:
        return -1;
    }
}

asm void bgUnloadSoundFix()
{
    // clang-format off
    nofralloc

    lwz     r3, 0x354(r3)
    li      r0, 0
    stw     r0, 0x10(r3)
    blr
    // clang-format on
}

const float defaultValues[2] = {0.6, 0.65};
asm void fix2DMapCharaSize()
{
    // clang-format off
    nofralloc

    lis r6, defaultValues@ha
    lfsu f0, defaultValues@l(r6)
    stfs f0, 0x18(r31)
    lfs f0, 4(r6)
    stfs f0, 0x1C(r31)

    // Original instruction
    cmpwi r0, 2
    blr
    // clang-format on
}

extern Instruction<1> Patch_SceneBuildPages;
extern Instruction<1> Patch_SceneShowBasePages;
extern Instruction<1> Patch_MainMenuKind;
extern Instruction<1> Patch_SceneGetBGM;
extern Instruction<1> Patch_SceneGetBGMGroup;
extern Instruction<1> Patch_LicenseSelect;
extern Instruction<1> Patch_BGUnloadSoundFix;

extern Instruction<6> Patch_EventExplanationPage_Events;
extern Instruction<25> Patch_EventExplanationPage_vtable;
extern Instruction<1> Patch_EventExplanationVolumeChange;

extern Instruction<1> Patch_2DMapCharaSizeFix;

void initMenu()
{
    if (getRegionChar() == 'E') {
        // Skip ESRB screen patch for NTSC-U
        Instruction<1>* esrbPatch =
            reinterpret_cast<Instruction<1>*>(0x8060409C);
        esrbPatch->m_instr[0] = 0x38600001;
        esrbPatch->flush();
    }

    ForcedHandleBypassPage::staticInit();
    SettingsPage::staticInit();
    initRaceMenu();

    Patch_SceneBuildPages.setB(buildPagesReplace);
    Patch_SceneShowBasePages.setB(showBasePagesReplace);

    Patch_MainMenuKind.m_instr[0] = 0x38600000 | UI::SceneKind::Globe;
    Patch_MainMenuKind.flush();

    Patch_LicenseSelect.setBL(patchLicenseSelectGetNextScene);

    Patch_BGUnloadSoundFix.setBL(bgUnloadSoundFix);

    Patch_2DMapCharaSizeFix.setBL(fix2DMapCharaSize);

    Patch_SceneGetBGM.setB(sceneGetBGMReplace);
    Patch_SceneGetBGMGroup.setB(sceneGetBGMGroupReplace);

    Patch_EventExplanationPage_Events.m_instr[2] =
        reinterpret_cast<u32>(&eventExplanationSelectEvent);
    Patch_EventExplanationPage_Events.m_instr[5] =
        reinterpret_cast<u32>(&eventExplanationBackEvent);
    Patch_EventExplanationPage_vtable.m_instr[4] =
        reinterpret_cast<u32>(&eventExplanationGetNextPage);
    Patch_EventExplanationPage_Events.flush();
    Patch_EventExplanationPage_vtable.flush();

    Patch_EventExplanationVolumeChange.setNop();
}