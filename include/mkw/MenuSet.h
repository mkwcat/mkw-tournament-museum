// MenuSet.h - MenuSet/RaceData implementation
//
// SPDX-License-Identifier: MIT

#pragma once
#include "GhostData.h"
#include <rvl/types.h>

// Documentation credit:
// https://github.com/SeekyCt/mkw-structures/blob/master/racedata.h
// Contributors:
//   Seeky (main documentation)
//   TheLordScruffy (main documentation)
//   WhatIsLoaf (ghost player type)
//   riidefi (ParameterFile)
//   CLF78 (local player count)
// References:
//   http://wiki.tockdom.com/wiki/Mission_Mode#mission_single.kmt
//   https://github.com/riidefi/mkw/blob/master/source/game/host_system/ParameterFile.hpp

// A class for loading a prm file from the disc, an unused file type
class ParamFile
{
public:
    virtual ~ParamFile();
    u8 fill[0x18];
};

struct MissionSetting {
    enum GameMode {
        MODE_Miniturbo = 0,
        MODE_LapRun01 = 1,
        MODE_LapRun02 = 2,
        MODE_Drift = 3,
        MODE_ItemBox = 4,
        MODE_EnemyDown01 = 5,
        MODE_EnemyDown02 = 6,
        MODE_EnemyDown03 = 7,
        MODE_CoinGet01 = 8,
        MODE_ToGate01 = 9,
        MODE_RocketStart = 10,
        MODE_ItemHit = 11,
        MODE_Wheelie = 12,
        MODE_Slipstream = 13
    };

    /* 0x00 */ u16 mrFile;
    /* 0x02 */ u16 gameMode;
    /* 0x04 */ u8 courseId;
    /* 0x05 */ u8 characterId;
    /* 0x06 */ u8 vehicleId;
    /* 0x07 */ u8 engineClass;
    /* 0x08 - 0x2C */ u8 fill_0x08[0x2C - 0x08];
    // Time limit in seconds
    /* 0x2C */ u16 timeLimit;
    /* 0x2E */ u8 unk_0x2E;
    /* 0x2F */ bool forceWiiWheel;
    /* 0x30 */ u32 scoreRequired;
    // Unused duplicates of scoreRequired???
    /* 0x34 - 0x48 */ u8 fill_0x34[0x48 - 0x34];
    /* 0x48 */ u16 cameraAngle;
    /* 0x4A */ u16 minimapObject;
    /* 0x4C */ u16 unk_0x4C;
    /* 0x4E */ u16 unk_0x4E;
    /* 0x50 */ u16 cannonFlag;
    /* 0x52 */ u16 unk_0x52;
    /* 0x54 */ u32 unk_0x54;
    /* 0x58 */ u16 cpuCount;
    /* 0x5A */ u8 cpu[22];
};

static_assert(sizeof(MissionSetting) == 0x70, "sizeof(MissionSetting) != 0x70");

class MenuSet : public ParamFile
{
public:
    /* 0x809BD728 */
    static MenuSet* sInstance;

    /* 0x80530038 */
    virtual ~MenuSet();
    virtual int FUN_80009ddc();
    virtual int FUN_80532078(); // just a blr
    virtual int FUN_80532074(); // just a blr
    virtual int FUN_80532070(); // just a blr

    class Player
    {
    public:
        /* 0x8052DC68 */
        virtual ~Player();
        /* 0x8052D96C */
        Player();

        /* 0x8052DAF0 */
        u32 computeGpRank();

        enum PlayerType {
            PLAYER_REAL_LOCAL,
            PLAYER_CPU,
            PLAYER_UNKNOWN2,
            PLAYER_GHOST,
            PLAYER_REAL_ONLINE,
            PLAYER_NONE
        };

        enum Team {
            TEAM_RED,
            TEAM_BLUE
        };

        /* 0x04 */ u8 unk_0x4;
        /* 0x05 */ u8 localPlayerId;
        /* 0x06 */ u8 controllerId;
        /* 0x08 */ u32 vehicleId;
        /* 0x0C */ u32 characterId;
        /* 0x10 */ u32 playerType;
        /* 0x14 - 0xCC */ u8 fill_0x14[0xCC - 0x14];
        /* 0xCC */ u32 team;
        /* 0xD0 - 0xD8 */ u8 fill_0xD0[0xD8 - 0xD0];
        /* 0xD8 */ u16 lastScore;
        /* 0xDA */ u16 score;
        /* 0xDC */ u16 unk_0xDC;
        /* 0xDE */ u16 gpRankScore;
        /* 0xE0 */ u8 unk_0xE0;
        /* 0xE1 */ u8 lastFinishPos;
        /* 0xE2 - 0xE8 */ u8 fill_0xE2[0xE8 - 0xE2];
        /* 0xE8 */ u16 rating; // online VR/BR
        /* 0xEA - 0xF0 */ u8 fill_0xEA[0xF0 - 0xEA];
    };

    static_assert(sizeof(Player) == 0xF0, "sizeof(Player) != 0xF0");

    class RaceSetting
    {
    public:
        virtual ~RaceSetting();
        /* 0x8052DBC8 */
        RaceSetting();

        /* 0x8052ED28 */
        void setupNextRaceInput(const RaceSetting* lastRace);

        enum EngineClass {
            CC_50 = 0,
            CC_100 = 1,
            CC_150 = 2,
            // Note: Battle mode actually sets it to 50cc (which is ignored by
            // code), but setting it to this in other modes results in Battle CC
            CC_BATTLE = 3
        };

        enum GameMode {
            MODE_GRAND_PRIX = 0,
            MODE_VS_RACE = 1,
            MODE_TIME_TRIAL = 2,
            MODE_BATTLE = 3,
            MODE_MISSION_TOURNAMENT = 4,
            MODE_GHOST_RACE = 5,
            MODE_6 = 6,
            MODE_PRIVATE_VS = 7,
            MODE_PUBLIC_VS = 8,
            MODE_PUBLIC_BATTLE = 9,
            MODE_PRIVATE_BATTLE = 10,
            MODE_AWARD = 11,
            MODE_CREDITS = 12
        };

        enum BattleMode {
            BATTLE_BALLOON = 0,
            BATTLE_COIN = 1
        };

        enum CpuSetting {
            CPU_EASY = 0,
            CPU_NORMAL = 1,
            CPU_HARD = 2,
            CPU_NONE = 3
        };

        enum ItemSetting {
            ITEM_BALANCED = 0,
            ITEM_FRANTIC = 1,
            ITEM_STRATEGIC = 2,
            ITEM_NONE = 3
        };

        enum ModeFlags {
            FLAG_MIRROR = 1 << 0,
            FLAG_TEAMS = 1 << 1,
            FLAG_TOURNAMENT = 1 << 2
        };

        /* 0x004 */ u8 playerCount;
        /* 0x005 */ u8 unk_0x5;
        /* 0x006 */ u8 localPlayerCount;
        /* 0x008 */ Player players[12];
        /* 0xB48 */ u32 courseId;
        /* 0xB4C */ u32 engineClass;
        /* 0xB50 */ u32 gameMode;
        // unsure, but 0 = player controlled, 1 = replay, 5 = opening camera
        // pan?
        /* 0xB54 */ u32 controlKind;
        /* 0xB58 */ u32 battleMode;
        /* 0xB5C */ u32 cpuSetting;
        /* 0xB60 */ u32 itemSetting;
        /* 0xB64 */ u8 hudPlayerIds[4];
        /* 0xB68 */ u32 cupId;
        /* 0xB6C */ u8 raceNum;
        /* 0xB6D */ u8 lapCount;
        /* 0xB6E */ u8 unk_0xB6E;
        /* 0xB6F */ u8 unk_0xB6F;
        /* 0xB70 */ u32 modeFlags;
        // Must be fixed for a specific race to replay properly
        /* 0xB74 */ u32 seedFixed;
        // Can change between race and replay
        /* 0xB78 */ u32 seedRandom;
        /* 0xB7C */ MissionSetting mission;
        /* 0xBEC */ GhostData* ghost;
    };

    static_assert(sizeof(RaceSetting) == 0xBF0, "sizeof(RaceSetting) != 0xBF0");

    /* 0x001C */ const u8* unk_0x1C;

    /* 0x0020 */ RaceSetting currentRace;
    /* 0x0C10 */ RaceSetting nextRace;
    /* 0x1800 */ RaceSetting unknownRace;

    /* 0x23F0 */ GhostData::RKGFile ghosts[2];
};

static_assert(sizeof(MenuSet) == 0x73F0, "sizeof(MenuSet) != 0x73F0");

// hack for asm blocks
extern u32 sInstance__7MenuSet;
