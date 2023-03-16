// RaceHudPage.h - Race HUD base page
//
// SPDX-License-Identifier: MIT

#pragma once
#include "UIInputManager.h"
#include "UIPage.h"
#include <rvl/types.h>

namespace UI
{

class RaceHudPage : public UIPage
{
public:
    /* 0x80624764 */
    virtual ~RaceHudPage();

    RaceHudPage()
    {
    }

    virtual int getNextPageID();
    virtual void _20();
    virtual void onInit();
    virtual void onDeinit();
    virtual void onOut();
    virtual void onUpdateBegin();
    virtual void onUpdateEnd();

    /* vt + 0x64 */ virtual s32 getPausePageID() = 0;
    /* vt + 0x68 */ virtual u32 getHudLayoutMask() = 0;
    /* vt + 0x6C */ virtual int _6C();
    /* vt + 0x70 */ virtual void onPause();
    /* vt + 0x74 */ virtual bool isRaceEnded(int hudIndex);
    /* vt + 0x78 */ virtual bool _78();
    /* vt + 0x7C */ virtual bool _7C();

    struct UnknownMember {
        UnknownMember()
          : unk_0x4C(0)
          , unk_0x4E(0)
          , unk_0x50(0)
          , unk_0x54(0)
          , unk_0x64(0)
        {
        }

        virtual ~UnknownMember();

        u16 unk_0x4C;
        u8 unk_0x4E;
        u8 unk_0x4F;
        u16 unk_0x50;
        u8 unk_0x52[2];
        u8 unk_0x54;
        u8 unk_0x55[0x64 - 0x55];
        u32 unk_0x64;
        u8 fill_0x68[0x80 - 0x68];
    };

    s32 m_nextPage;

    /* 0x48 */ UnknownMember unk_0x48;
    /* 0x80 */ UIInputManagerRace m_inputs;
    u8 fill_0x1C4[0x1DC - 0x1C4];

    INSTANTIATE_TYPEINFO;
};

static_assert(sizeof(RaceHudPage) == 0x1DC, "sizeof(RaceHudPage) != 0x1DC");

} // namespace UI
