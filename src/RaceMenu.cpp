// RaceMenu.cpp - Pause menu and end screens
//
// SPDX-License-Identifier: MIT

#include "RaceMenu.h"
#include "CompFile.h"
#include "Replay.h"
#include "UI.h"
#include "patch.h"
#include <asm.h>
#include <mkw/MenuSet.h>
#include <mkw/UI/RaceHudPage.h>
#include <mkw/UI/RaceMenuPage.h>
#include <mkw/UI/UIPage.h>

const int sEndScreenButtons[5] = {
  UI::RaceMenu::ButtonRestart,       UI::RaceMenu::ButtonChangeCharacter,
  UI::RaceMenu::ButtonChangeMission, UI::RaceMenu::ButtonQuit,
  UI::RaceMenu::ButtonReplay,
};
const int sPauseScreenButtons[5] = {
  UI::RaceMenu::ButtonContinue,
  UI::RaceMenu::ButtonRestart,
  UI::RaceMenu::ButtonChangeCharacter,
  UI::RaceMenu::ButtonChangeMission,
  UI::RaceMenu::ButtonQuit,
};

class EventAfterMenuPage : public UI::RaceMenuPage
{
public:
    EventAfterMenuPage()
      : m_340(0)
    {
    }

    int _68()
    {
        return m_340;
    }

    int getButtonCount() const
    {
        return 5;
    }

    const int* getButtonList() const
    {
        return sEndScreenButtons;
    }

    bool isPauseMenu() const
    {
        return false;
    }

    const char* getButtonCtrlName() const
    {
        return "AfterMenuOfflineEvent";
    }

    int m_33C;
    int m_340;

public:
    INSTANTIATE_TYPEINFO;
};

TYPEINFO_DERIVED(EventAfterMenuPage, UI::RaceMenuPage);

class EventPauseMenuPage : public UI::RaceMenuPage
{
public:
    EventPauseMenuPage()
      : m_340(0)
    {
    }

    int _68()
    {
        return m_340;
    }

    int getButtonCount() const
    {
        return 5;
    }

    const int* getButtonList() const
    {
        return sPauseScreenButtons;
    }

    bool isPauseMenu() const
    {
        return true;
    }

    const char* getButtonCtrlName() const
    {
        return "PauseMenuOfflineEvent";
    }

    int m_33C;
    int m_340;

public:
    INSTANTIATE_TYPEINFO;
};

TYPEINFO_DERIVED(EventPauseMenuPage, UI::RaceMenuPage);

class ReplayHud : public UI::RaceHudPage
{
public:
    ReplayHud()
    {
        m_nextPage = -1;
    }

    s32 getPausePageID()
    {
        return 0x39;
    }

    // Decompilation of the function at 0x8085896C.
    // I don't know what all the mask bits are.
    virtual u32 getHudLayoutMask()
    {
        MenuSet::RaceSetting* set = &MenuSet::sInstance->currentRace;

        if (set->modeFlags & MenuSet::RaceSetting::FLAG_TOURNAMENT) {
            switch (set->gameMode) {
            case MenuSet::RaceSetting::MODE_VS_RACE:
                return 0x87E;
            case MenuSet::RaceSetting::MODE_TIME_TRIAL:
                return 0x86E;
            }

            switch (set->mission.gameMode) {
            case MissionSetting::MODE_LapRun01:
                return 0x86E;
            case MissionSetting::MODE_LapRun02:
                return 0x87E;

            case MissionSetting::MODE_EnemyDown01:
            case MissionSetting::MODE_EnemyDown02:
            case MissionSetting::MODE_EnemyDown03:
                return 0x2C4E;
            }
        } else {
            switch (set->mission.gameMode) {
            // Apparently these are both the same for non-tournament mission
            // mode
            case MissionSetting::MODE_LapRun01:
            case MissionSetting::MODE_LapRun02:
                return 0x87E;
            }
        }

        return 0xC4E;
    }

public:
    INSTANTIATE_TYPEINFO;
};

TYPEINFO_DERIVED(ReplayHud, UI::RaceHudPage);

void buildTournamentPages(UI::UIPageManager* scene)
{
    scene->buildPage(0x16);
    scene->buildPage(0x35);
    scene->buildPage(0x3A);
    {
        EventPauseMenuPage* page = new EventPauseMenuPage();
        scene->setPage(0x1B, page);
        page->init(0x1B);
    }
    {
        EventAfterMenuPage* page = new EventAfterMenuPage();
        scene->setPage(0x26, page);
        page->init(0x26);
    }
}

void buildTournamentReplayPages(UI::UIPageManager* scene)
{
    scene->buildPage(0x39);
    scene->buildPage(0x3A);
    {
        ReplayHud* page = new ReplayHud();
        scene->setPage(0x16, page);
        page->init(0x16);
    }
    {
        EventAfterMenuPage* page = new EventAfterMenuPage();
        scene->setPage(0x26, page);
        page->init(0x26);
    }
}

ASM_FUNCTION(void hudWatchReplayHook(),
             // clang-format off
    li      R4, -1;

    cmpwi   R0, 0x2D;
    bnelr;

    li      R4, TOURNAMENT_SCENE_ID;
    blr;
             // clang-format on
)

ASM_FUNCTION(void hudQuitReplayHook(),
             // case 0x2F
             li R4, 0x21;
             beqlr - ;

             cmpwi R0, TOURNAMENT_SCENE_ID; li R4, 0x26; beqlr - ;

             li R4, -1; blr;
             // clang-format on
)

int resultMusicHook(int bgmId)
{
    if (MenuSet::sInstance->currentRace.modeFlags &
        MenuSet::RaceSetting::FLAG_TOURNAMENT) {
        // Replay end depends on this sound not looping. Unfortunately not much
        // to do about the results that don't have a fanfare only version.
        if (isTournamentReplay()) {
            if (bgmId == 0x6F || bgmId == 0x70)
                return 0x63;
            return 0x65;
        }

        // Let's do this check properly. I'm assuming that was actually a bug
        // and it should play the boss fanfare if the intro setting is 3.
        if ((bgmId == 0x70 || bgmId == 0x71) &&
            CompFile::sInstance->getHeader()->objective.introSetting == 3)
            return 0x6F;
    }

    return bgmId;
}

extern Instruction<24> Patch_ChangeMissionCase;
extern Instruction<1> Patch_HudWatchReplayCase;
extern Instruction<4> Patch_QuitReplayCase;
extern Instruction<1> Patch_ResultMusic;

void initRaceMenu()
{
    Patch_ChangeMissionCase.m_instr[8] = 0x38800000 | 0x85;
    Patch_ChangeMissionCase.m_instr[16] = 0x36800000 | 0x2D;
    Patch_ChangeMissionCase.flush();

    Patch_HudWatchReplayCase.setBL(hudWatchReplayHook);

    Patch_QuitReplayCase.setNop(0);
    Patch_QuitReplayCase.setBL(hudQuitReplayHook, 3);

    Patch_ResultMusic.setB(resultMusicHook);
}
