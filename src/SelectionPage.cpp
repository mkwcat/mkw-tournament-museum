// SelectionPage.cpp - Tournament select page
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

#include "SelectionPage.h"
#include "CompFile.h"
#include "UI.h"
#include <mkw/common.h>
#include <stdio.h>

TYPEINFO_DERIVED(SelectionPage, UI::UIPage);

enum
{
    MSG_TOURNAMENTS_PAGE_TITLE = 0x27F0,
    MSG_TOURNAMENT_NUMBER_PAGE_TITLE = 0x27F1
};

namespace CompMode
{
enum E
{
    TimeTrial,
    VSRace,
    SpecialTimeTrial,
    EnemyScore,
    BossBattle,
    BossRace,
    Coins,
    Gates,
    BossBattleReplica
};
} // namespace CompMode

struct CompNameData {
    Course::E course;
    CompMode::E mode;
};

static const CompNameData compNameData[49] = {
    /* c01 - c09 */
    {Course::Mario_Circuit, CompMode::VSRace},
    {Course::GBA_Battle_Course_3, CompMode::Gates},
    {Course::Galaxy_Colosseum, CompMode::BossBattle},
    {Course::Mushroom_Gorge, CompMode::TimeTrial},
    {Course::Coconut_Mall, CompMode::Coins},
    {Course::DS_Twilight_House, CompMode::VSRace},
    {Course::N64_DKs_Jungle_Parkway, CompMode::BossRace},
    {Course::Koopa_Cape, CompMode::Gates},
    {Course::N64_Skyscraper, CompMode::SpecialTimeTrial},

    /* c10 - c19 */
    {Course::SNES_Mario_Circuit_3, CompMode::Coins},
    {Course::Thwomp_Desert, CompMode::BossBattle},
    {Course::Luigi_Circuit, CompMode::VSRace},
    {Course::Maple_Treeway, CompMode::Coins},
    {Course::N64_Mario_Raceway, CompMode::SpecialTimeTrial},
    {Course::Warios_Gold_Mine, CompMode::BossRace},
    {Course::DK_Summit, CompMode::Gates},
    {Course::Toads_Factory, CompMode::TimeTrial},
    {Course::Funky_Stadium, CompMode::Coins},
    {Course::Block_Plaza, CompMode::TimeTrial},

    /* c20 - c29 */
    {Course::GBA_Bowser_Castle_3, CompMode::Gates},
    {Course::SNES_Battle_Course_4, CompMode::Coins},
    {Course::N64_Bowsers_Castle, CompMode::BossRace},
    {Course::GCN_Waluigi_Stadium, CompMode::Gates},
    {Course::DS_Peach_Gardens, CompMode::SpecialTimeTrial},
    {Course::Sunset_Luigi_Circuit, CompMode::VSRace},
    {Course::Chain_Chomp_Roulette, CompMode::Coins},
    {Course::Grumble_Volcano, CompMode::TimeTrial},
    {Course::Galaxy_Colosseum, CompMode::BossBattle},
    {Course::GCN_Peach_Beach, CompMode::Coins},

    /* c30 - c39 */
    {Course::DS_Yoshi_Falls, CompMode::VSRace},
    {Course::GBA_Shy_Guy_Beach, CompMode::EnemyScore},
    {Course::Bowsers_Castle, CompMode::TimeTrial},
    {Course::GCN_Cookie_Land, CompMode::VSRace},
    {Course::GCN_Mario_Circuit, CompMode::SpecialTimeTrial},
    {Course::Daisy_Circuit, CompMode::Gates},
    {Course::Dry_Dry_Ruins, CompMode::VSRace},
    {Course::Rainbow_Road, CompMode::SpecialTimeTrial},
    {Course::DS_Desert_Hills, CompMode::EnemyScore},
    {Course::Delfino_Pier, CompMode::SpecialTimeTrial},

    /* c40 - c49 */
    {Course::GCN_DK_Mountain, CompMode::Gates},
    {Course::N64_Sherbet_Land, CompMode::VSRace},
    {Course::Mario_Circuit, CompMode::EnemyScore},
    {Course::Luigi_Circuit, CompMode::VSRace},
    {Course::GCN_Peach_Beach, CompMode::SpecialTimeTrial},
    {Course::Moonview_Highway, CompMode::TimeTrial},
    {Course::DS_Delfino_Square, CompMode::TimeTrial},
    {Course::Mario_Circuit, CompMode::VSRace},
    {Course::N64_Bowsers_Castle, CompMode::BossRace},
    {Course::Galaxy_Colosseum, CompMode::BossBattle},
};

static inline int compExplanationMid(int compId)
{
    return 10100 + compId - 1;
}

SelectionPage::SelectionPage()
    : mf_imp_onSelectEvent(this, &SelectionPage::onSelectEvent),
      mf_imp_onFreeToSelectEvent(this, &SelectionPage::onFreeToSelectEvent),
      mf_imp_onBackEvent(this, &SelectionPage::onBackEvent),
      mf_imp_onArrowRightEvent(this, &SelectionPage::onArrowRightEvent),
      mf_imp_onArrowLeftEvent(this, &SelectionPage::onArrowLeftEvent)
{
    m_nextPage = -1;
}

SelectionPage::~SelectionPage()
{
}

void SelectionPage::updatePageNumText()
{
    UI::MsgRes::FormatParam param;
    param.intParam = m_pageNum + 1;
    param.intParam2 = 5;
    m_pageNumControl.setMessage(0x7D9, &param);
}

void SelectionPage::updateButtonTexture()
{
    for (int i = 0; i < 10; i++) {
        char texture[16];
        snprintf(texture, 16, "comp%02d", buttonCompId(i));
        m_buttons[i].setTexture("chara", texture);
        UI::MsgRes::FormatParam param;
        param.intParam = buttonCompId(i);

        if (buttonCompId(i) == 0) {
            m_buttons[i].setMessage(0, nullptr);
        } else {
            m_buttons[i].setMessage(0x27E8, &param);
        }
    }
}

void SelectionPage::updateCompetitionName()
{
    if (m_selectedCompId == 0) {
        m_compName.setMessage("text", 0x1B58, 0);
        m_compName.setMessage("text_shadow", 0x1B58, 0);

        m_compName.setMessage("mode_text", 0x27F2, 0);
        m_compName.setMessage("mode_text_shadow", 0x27F2, 0);
        return;
    }
    if (m_selectedCompId == -100)
        return;

    const CompNameData* data = &compNameData[m_selectedCompId - 1];

    int courseMid = msgIdForCourse(data->course);
    m_compName.setMessage("text", courseMid, 0);
    m_compName.setMessage("text_shadow", courseMid, 0);

    m_compName.setMessage("mode_text", 0x27D8 + data->mode, 0);
    m_compName.setMessage("mode_text_shadow", 0x27D8 + data->mode, 0);

    char texture[16];
    snprintf(texture, 16, "id%02d", data->course);
    m_compName.setTexture("course_bg", texture);
}

int SelectionPage::buttonCompId(int buttonId)
{
    return m_pageNum * 10 + buttonId;
}
int SelectionPage::compIdButton(int compId)
{
    return compId % 10;
}

void SelectionPage::onInit()
{
    m_inputs.init(1, 0);

    setInputManager(&m_inputs);
    initControlGroup(15);

    for (int i = 0; i < 10; i++) {
        setControl(i, &m_buttons[i], 0);

        char name[16];
        snprintf(name, 16, "Button%d", i);

        m_buttons[i].readLayout("button", "CompetitionButton", name, 1, 0,
                                false);
        m_buttons[i].setSelectFunction(&mf_imp_onSelectEvent, 0);
        m_buttons[i].setFreeToSelectFunction(&mf_imp_onFreeToSelectEvent);

        m_buttons[i].m_id = i;
    }

    m_selectedCompId = s_lastCompId;
    m_pageNum = m_selectedCompId / 10;
    m_selectedButtonId = compIdButton(m_selectedCompId);

    m_buttons[m_selectedButtonId].setSelected(0);

    setControl(10, &m_arrows, 0);

    m_arrows.readLayout("button", "FriendListArrowRight", "ButtonArrowRight",
                        "FriendListArrowLeft", "ButtonArrowLeft", 1, 0, false);
    // This is normally done using two functions in the SheetSelectControl
    m_arrows.mf_onSelectRight = &mf_imp_onArrowRightEvent;
    m_arrows.mf_onSelectLeft = &mf_imp_onArrowLeftEvent;

    {
        setControl(11, &m_pageNumControl, 0);

        UI::CtrlRes ctrl(&m_pageNumControl);
        ctrl.readFile("control", "TimeAttackGhostListPageNum",
                      "TimeAttackGhostListPageNum", nullptr);
    }
    {
        setControl(12, &m_compName, 0);

        UI::CtrlRes ctrl(&m_compName);
        ctrl.readFile("control", "CompetitionName", "CompetitionName", nullptr);
    }

    setControl(13, &m_backButton, 0);

    m_backButton.initLayout(1);
    m_backButton.setSelectFunction(&mf_imp_onSelectEvent, 0);
    m_backButton.setFreeToSelectFunction(&mf_imp_onFreeToSelectEvent);

    setControl(14, &m_titleText, 0);

    m_titleText.initLayout(0);
    m_titleText.setMessage(MSG_TOURNAMENTS_PAGE_TITLE, 0);

    m_inputs.setScreenWrapSetting(2);
    m_inputs.configureInput(UI::INPUT_BACK, &mf_imp_onBackEvent, 0, 0);

    updatePageNumText();
    updateCompetitionName();
    updateButtonTexture();
}

void SelectionPage::onSelectEvent(UI::PushButton* button, int r5)
{
    // -100 represents the on-screen back button
    if (button->m_id == -100) {
        f32 delay = button->getSelectDelay();
        toNextScene(0x42, UI::UIPage::SLIDE_BACK, delay);
        return;
    }

    int compId = buttonCompId(button->m_id);
    s_lastCompId = compId;
    if (compId == 0) {
        // Settings
        m_nextPage = -1;
        f32 delay = button->getSelectDelay();
        toNextScene(SETTINGS_SCENE_ID, SLIDE_FORWARD, delay);
        return;
    }

    // Search for the competition messages. The text on the event
    // explanation screen isn't fetched from BMG files because it's
    // meant to be stored in the save file. This is a little hacky
    // because it hijacks the BMG used by the button that was just
    // selected.
    int titleMid = MSG_TOURNAMENT_NUMBER_PAGE_TITLE;
    int explanationMid = compExplanationMid(compId);

    const UI::MsgRes* bmg = &button->m_bmg;
    int titleIndex = bmg->getIndexFromMid(titleMid);
    int explanationIndex = bmg->getIndexFromMid(explanationMid);

    const wchar_t* titleText = L"---";
    const wchar_t* explanationText = L"---";
    if (titleIndex != -1)
        titleText = bmg->getTextFromIndex(titleIndex);
    if (explanationIndex != -1)
        explanationText = bmg->getTextFromIndex(explanationIndex);

    CompFile::sInstance->setText(titleText, explanationText);
    CompFile::sInstance->switchCompetition(compId);
    m_nextPage = 0xB8;

    f32 delay = button->getSelectDelay();
    toOut(SLIDE_FORWARD, delay);
}

void SelectionPage::onFreeToSelectEvent(UI::PushButton* button, int r5)
{
    m_selectedButtonId = button->m_id;
    m_selectedCompId = buttonCompId(button->m_id);
    updateCompetitionName();
}

void SelectionPage::onBackEvent(int r4, int r5)
{
    m_nextPage = -1;
    toNextScene(0x42, UI::UIPage::SLIDE_BACK, 0);
}

void SelectionPage::onArrowRightEvent(UI::SheetSelectControl* arrow, int r5)
{
    m_pageNum++;
    if (m_pageNum > 4)
        m_pageNum = 0;
    updatePageNumText();
    updateButtonTexture();

    // Deselect arrows and select main button
    if (m_selectedButtonId < 5) {
        m_buttons[0].freeToSelect(0);
        return;
    }
    m_buttons[5].freeToSelect(0);
}

void SelectionPage::onArrowLeftEvent(UI::SheetSelectControl* arrow, int r5)
{
    m_pageNum--;
    if (m_pageNum < 0)
        m_pageNum = 4;
    updatePageNumText();
    updateButtonTexture();

    // Deselect arrows and select main button
    if (m_selectedButtonId < 5) {
        m_buttons[4].freeToSelect(0);
        return;
    }
    m_buttons[9].freeToSelect(0);
}

int SelectionPage::getNextPageID()
{
    return m_nextPage;
}

int SelectionPage::s_lastCompId = 0;