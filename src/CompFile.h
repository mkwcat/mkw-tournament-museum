// CompFile.h - Competition file reader and save data manager
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

#pragma once
#include "File.h"
#include <egg/eggFile.h>
#include <egg/eggTaskThread.h>
#include <mkw/GhostData.h>
#include <mkw/LeaderboardEntry.h>
#include <mkw/MiiData.h>
#include <mkw/common.h>
#include <rvl/types.h>

#define COMP_COUNT 49
#define SAVE_VERSION 0

namespace RKC
{

struct FileObjective {
    u32 rkcoMagic;
    u16 gameMode;
    u8 courseId;
    u8 engineClass;
    u8 lapCount;
    u8 pad_0x9;
    enum
    {
        RESTRICTION_KARTS_ONLY,
        RESTRICTION_BIKES_ONLY,
        RESTRICTION_NONE
    };
    u16 vehicleRestriction;
    u16 cameraAngle;
    u16 minimapObject;
    u16 unknown_0x10;
    u16 unknown_0x12;
    u16 cannonFlag;
    u16 cpuCount;
    u8 cpu[22];
    bool forceWiiWheel;
    u8 pad_0x2F;
    u16 commonObjSetting;
    u16 requiredScore;
    u8 introSetting;
    u8 pad_0x35;
    u16 unknown_0x36;
    u8 pad_0x38[2];
    u16 checksum;
};
static_assert(sizeof(FileObjective) == 0x3C, "sizeof(FileObjective) != 0x3C");

struct FileHeader {
    u32 rkctMagic;
    u32 fileSize;
    u32 archiveOffset;
    u32 unknown;
    FileObjective objective;
};
static_assert(sizeof(FileHeader) == 0x4C, "sizeof(FileHeader) != 0x4C");

} // namespace RKC

struct CompSaveFile {
    char magic[4]; // "MKTM" 0x4D4B544D
    u32 version;
    u8 pad[8];

    struct LdbEntry {
        MiiData mii; // size 0x4C

        u32 minutes : 7;
        u32 seconds : 7;
        u32 milliseconds : 10;

        u32 vehicleId : 6;
        u8 isEnabled : 1;
        u8 characterId : 7;
        u8 controllerId : 3;

        u8 unk_51_3 : 5;
        u8 fill[14];
    } __attribute__((packed));

    struct Data {
        enum GhostSaveMode
        {
            GHOST_SAVE_ALL = 0,
            GHOST_SAVE_BEST_TIME = 1,
            GHOST_SAVE_NONE = 2
        };

        u8 ghostSaveMode;
        u8 reserved[0x100 - 1]; // for future settings

        LdbEntry ldb[5 * COMP_COUNT];
    };

    Data data[4];
};

class CompFile
{
public:
    static CompFile* sInstance;

    virtual ~CompFile();
    CompFile();

    bool isTaskExist() const;
    bool isFileAvailable() const;
    u8* getData();
    RKC::FileHeader* getHeader();
    static int ldbEntryIndex(int compId);

    void switchCompetition(int compId);
    void requestWriteSaveFile();
    void requestSaveGhostData();

    void readFile();
    void setupLeaderboard();
    void getSaveDataPath(char* path);
    void getGhostDataPath(char* path, u32 num);
    void getGhostDataDir(char* path, int compId);
    void openSaveFile();
    bool readSaveFile();
    bool createSaveFile();
    void writeSaveTask();
    CompSaveFile::Data* getLicenseSaveData();
    void setText(const wchar_t* title, const wchar_t* explanation);
    void writeGhostDataTask();
    bool shouldGhostSave(GhostData::RaceTime* time);

    void getLdbEntry(u8 position, LeaderboardEntry* entry);
    int getTimeLdbPosition(GhostData::RaceTime* time);
    void insertTimeInLdb(LeaderboardEntry* entry, u32 position);

    const wchar_t* m_compTitle;
    const wchar_t* m_compExplanation;
    bool m_forceHandleDisabled;

private:
    EGG::TaskThread* m_thread;

    NandFile* m_file;

public:
    CompSaveFile::LdbEntry* m_leaderboard;
    CompSaveFile m_saveData ATTRIBUTE_ALIGN(32);

    GhostData m_ghost;
    GhostData::RKGFile m_tempRkg;

    u8 m_ghostCPUs[0x14];

    union {
        u8 m_rkcData[0x4800] ATTRIBUTE_ALIGN(32);
        RKC::FileHeader m_rkc;
    };

public:
    enum SaveError
    {
        SAVE_WAITING = 0,
        SAVE_OK = 1,
        SAVE_EUNKNOWN = 2,
        SAVE_EOPEN = 3,
        SAVE_EWRITE = 4,
        SAVE_EREAD = 5,
        SAVE_EVERSION = 6,
        SAVE_EFORMAT = 7,
        SAVE_EIPC = 8
    };
    SaveError m_saveDataStatus;
    s32 m_saveFsError;
    SaveError m_ghostDataStatus;
    s32 m_ghostFsError;

    int m_compId;
    bool m_isFileAvailable;
};

void initCompFilePatches();