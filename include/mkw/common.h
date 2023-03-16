// common.h - Common MKW definitions and functions
//
// SPDX-License-Identifier: MIT

#pragma once
#include <rvl/types.h>

namespace Course
{
enum E {
    Luigi_Circuit = 0x08,
    Moo_Moo_Meadows = 0x01,
    Mushroom_Gorge = 0x02,
    Toads_Factory = 0x04,

    Mario_Circuit = 0x00,
    Coconut_Mall = 0x05,
    DK_Summit = 0x06,
    Warios_Gold_Mine = 0x07,

    Daisy_Circuit = 0x09,
    Koopa_Cape = 0x0F,
    Maple_Treeway = 0x0B,
    Grumble_Volcano = 0x03,

    Dry_Dry_Ruins = 0x0E,
    Moonview_Highway = 0x0A,
    Bowsers_Castle = 0x0C,
    Rainbow_Road = 0x0D,

    GCN_Peach_Beach = 0x10,
    DS_Yoshi_Falls = 0x14,
    SNES_Ghost_Valley_2 = 0x19,
    N64_Mario_Raceway = 0x1A,

    N64_Sherbet_Land = 0x1B,
    GBA_Shy_Guy_Beach = 0x1F,
    DS_Delfino_Square = 0x17,
    GCN_Waluigi_Stadium = 0x12,

    DS_Desert_Hills = 0x15,
    GBA_Bowser_Castle_3 = 0x1E,
    N64_DKs_Jungle_Parkway = 0x1D,
    GCN_Mario_Circuit = 0x11,

    SNES_Mario_Circuit_3 = 0x18,
    DS_Peach_Gardens = 0x16,
    GCN_DK_Mountain = 0x13,
    N64_Bowsers_Castle = 0x1C,

    Block_Plaza = 0x21,
    Delfino_Pier = 0x20,
    Funky_Stadium = 0x23,
    Chain_Chomp_Roulette = 0x22,
    Thwomp_Desert = 0x24,

    SNES_Battle_Course_4 = 0x27,
    GBA_Battle_Course_3 = 0x28,
    N64_Skyscraper = 0x29,
    GCN_Cookie_Land = 0x25,
    DS_Twilight_House = 0x26,

    Galaxy_Colosseum = 0x36,
    Sunset_Luigi_Circuit = 0x3A,

    Winning_Demo = 0x37,
    Losing_Demo = 0x38,
    Draw_Dmeo = 0x39 // lol
};
} // namespace Course

int msgIdForCourse(int course);
