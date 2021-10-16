// CompFile.cpp - Competition file reader and save data manager
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

#include "CompFile.h"
#include "util.h"
#include <egg/eggDvdFile.h>
#include <mkw/MenuSet.h>
#include <mkw/RKContext.h>
#include <mkw/Random.h>
#include <mkw/SaveDataManager.h>
#include <patch.h>
#include <rvl/ipc.h>
#include <rvl/nand.h>
#include <rvl/os.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#define MKWCOMP_ROOT "/mkwcomp"
#define MKWCOMP_SAVE_ROOT MKWCOMP_ROOT "/save"

CompFile compFileInstance;
CompFile* CompFile::sInstance = &compFileInstance;

bool CompFile::isTaskExist() const
{
    return m_thread->isTaskExist();
}

bool CompFile::isFileAvailable() const
{
    return m_isFileAvailable;
}

u8* CompFile::getData()
{
    return m_rkcData;
}

RKC::FileHeader* CompFile::getHeader()
{
    return &m_rkc;
}

int CompFile::ldbEntryIndex(int compId)
{
    return (compId - 1) * 5;
}

CompFile::CompFile()
{
    m_thread = EGG::TaskThread::create(2, 20, 0x1000, nullptr);
    m_isFileAvailable = false;

    if (isRiivolution()) {
        RiivoFS::initialize();
        m_file = new RiivoFile();
    } else {
        m_file = new NandFile();
    }

    openSaveFile();
    m_ghostDataStatus = SAVE_OK;
}

CompFile::~CompFile()
{
}

static inline void getCompPath(int compId, char* out)
{
    sprintf(out, "/Race/Competition/comp%02d.rkc", compId);
}

void CompFile::readFile()
{
    char path[64];
    getCompPath(m_compId, path);

    EGG::DvdFile file;
    if (!file.open(path)) {
        OSReport("ERROR: Failed to open competition %d!\n", m_compId);
        return;
    }

    u32 fileSize = file.getFileSize();
    if (fileSize < sizeof(RKC::FileHeader)) {
        OSReport("ERROR: File is too small to be a competition file (id %d)!\n",
                 m_compId);
        return;
    }
    if (fileSize > sizeof(m_rkcData)) {
        OSReport(
            "ERROR: Competition file is too big to fit in buffer! (id %d)\n",
            m_compId);
        return;
    }

    s32 result = file.readData(reinterpret_cast<void*>(m_rkcData), fileSize, 0);
    if (result != fileSize) {
        OSReport("ERROR: Failed to read header from competition %d!\n",
                 m_compId);
        return;
    }

    m_isFileAvailable = true;
}

void CompFile::setupLeaderboard()
{
    m_leaderboard = &getLicenseSaveData()->ldb[ldbEntryIndex(m_compId)];
}

static const char* savePathRoot()
{
    if (isRiivolution())
        return MKWCOMP_SAVE_ROOT;

    static char sHomeDir[IPC_MAX_PATH + 1];
    static bool sGotHomeDir = false;

    if (!sGotHomeDir) {
        NANDGetHomeDir(sHomeDir);
        sGotHomeDir = true;
    }

    return sHomeDir;
}

void CompFile::getSaveDataPath(char* path)
{
    snprintf(path, 128, "%s/mktmsave.bin", savePathRoot());
}

void CompFile::openSaveFile()
{
    m_saveDataStatus = SAVE_WAITING;

    char path[128];
    getSaveDataPath(path);

    if (isRiivolution() && !RiivoFS::sInstance->dirExists(savePathRoot())) {
        RiivoFS::sInstance->createDir(savePathRoot());
    }

    bool ret = m_file->openCreate(path, NAND_MODE_RW);

    if (!ret) {
        OSReport("ERROR: Failed to open save file\n");
        m_saveFsError = m_file->getFSError();
        m_saveDataStatus = SAVE_EOPEN;
        return;
    }

    if (m_file->getFileSize() == 0) {
        ret = createSaveFile();
    } else {
        ret = readSaveFile();
    }
    m_file->close();

    if (ret) {
        m_saveDataStatus = SAVE_OK;
    }
}

bool CompFile::readSaveFile()
{
    if (m_file->getFileSize() < sizeof(CompSaveFile)) {
        OSReport("ERROR: Save file invalid size\n");
        m_saveDataStatus = SAVE_EFORMAT;
        return false;
    }

    s32 ret = m_file->readData(&m_saveData, sizeof(m_saveData), 0);
    if (ret != sizeof(m_saveData)) {
        OSReport("ERROR: Failed to read save data\n");
        m_saveFsError = m_file->getFSError();
        m_saveDataStatus = SAVE_EREAD;
        return false;
    }

    return true;
}

void CompFile::writeSaveTask()
{
    m_saveDataStatus = SAVE_WAITING;

    char path[128];
    getSaveDataPath(path);

    bool ret = m_file->open(path, NAND_MODE_WRITE);

    if (!ret) {
        OSReport("ERROR: Failed to open save file\n");
        m_saveDataStatus = SAVE_EOPEN;
        m_saveFsError = m_file->getFSError();
        return;
    }

    s32 sret = m_file->writeData(&m_saveData, sizeof(m_saveData), 0);
    m_file->close();

    if (sret != sizeof(m_saveData)) {
        OSReport("ERROR: Save write failed!\n");
        m_saveDataStatus = SAVE_EWRITE;
        m_saveFsError = m_file->getFSError();
        return;
    }

    m_saveDataStatus = SAVE_OK;
}

bool CompFile::createSaveFile()
{
    memset(&m_saveData, 0, sizeof(m_saveData));
    m_saveData.magic[0] = 'M';
    m_saveData.magic[1] = 'K';
    m_saveData.magic[2] = 'T';
    m_saveData.magic[3] = 'M';
    m_saveData.version = SAVE_VERSION;
    m_saveData.pad[0] = 0;
    m_saveData.pad[1] = 0;

    for (int i = 0; i < 4; i++) {
        m_saveData.data[i].ghostSaveMode = CompSaveFile::Data::GHOST_SAVE_ALL;
        memset(m_saveData.data[i].reserved, 0,
               sizeof(m_saveData.data[i].reserved));
        memset(&m_saveData.data[i].ldb, 0, sizeof(m_saveData.data[i].ldb));
    }

    s32 sret = m_file->writeData(&m_saveData, sizeof(m_saveData), 0);

    if (sret != sizeof(m_saveData)) {
        OSReport("ERROR: Save write failed!\n");
        m_saveFsError = m_file->getFSError();
        m_saveDataStatus = SAVE_EWRITE;
        return false;
    }

    return true;
}

static char getFilenameChar(wchar_t wc)
{
    if (wc > 0xFF)
        return '_';

    switch (wc) {
    case '/':
    case '?':
    case '<':
    case '>':
    case '\\':
    case ':':
    case '*':
    case '|':
    case '"':
    case '^':
        return '_';

    default:
        return (char)wc;
    }
}

void CompFile::getGhostDataPath(char* path, u32 num)
{
    char asciiMiiName[10];
    for (int i = 0; i < 10; i++) {
        asciiMiiName[i] = getFilenameChar(m_ghost.m_mii.name[i]);
        if (asciiMiiName[i] == 0)
            break;
    }

    const char* format =
        num == 0 ? "%s/comp%02u/comp%02u - %.10s - %02um %02us %03um.rkg"
                 : "%s/comp%02u/comp%02u - %.10s - %02um %02us %03um - %u.rkg";
    snprintf(path, 128, format, savePathRoot(), m_compId, m_compId,
             asciiMiiName, m_ghost.m_finishTime.minutes,
             m_ghost.m_finishTime.seconds, m_ghost.m_finishTime.milliseconds,
             num);
}

void CompFile::getGhostDataDir(char* path, int compId)
{
    snprintf(path, 128, "%s/comp%02u", savePathRoot(), compId);
}

void CompFile::writeGhostDataTask()
{
    m_ghostDataStatus = SAVE_WAITING;

    char path[128];
    getGhostDataDir(path, m_compId);

    if (!RiivoFS::sInstance->dirExists(path)) {
        s32 ret = RiivoFS::sInstance->createDir(path);
        if (ret < 0) {
            m_ghostFsError = ret;
            m_ghostDataStatus = SAVE_EIPC;
            return;
        }
    }

    for (u32 num = 0;; num++) {
        getGhostDataPath(path, num);
        bool ret = m_file->open(path, NAND_MODE_READ);
        if (!ret)
            break;
        m_file->close();
    }

    bool ret = m_file->openCreate(path, NAND_MODE_WRITE);

    if (!ret) {
        OSReport("Failed to open ghost file\n");
        m_ghostFsError = m_file->getFSError();
        m_ghostDataStatus = SAVE_EOPEN;
        return;
    }

    GhostData::RKGFile* rkg = SaveDataManager::sInstance->m_rkgFile;

    memset(&m_tempRkg, 0, sizeof(GhostData::RKGFile));
    m_ghost.makeRKG(&m_tempRkg);
    m_tempRkg.compress(rkg);

    s32 sret = m_file->writeData(rkg, rkg->getFileSize(), 0);
    m_file->close();

    if (sret != rkg->getFileSize()) {
        OSReport("ERROR: Ghost write failed!\n");
        m_ghostFsError = m_file->getFSError();
        m_ghostDataStatus = SAVE_EWRITE;
        return;
    }

    m_ghostDataStatus = SAVE_OK;
}

CompSaveFile::Data* CompFile::getLicenseSaveData()
{
    return &m_saveData.data[RKContext::sInstance->m_98->m_licenseId];
}

static void taskEntry(void* arg)
{
    CompFile* object = reinterpret_cast<CompFile*>(arg);
    object->readFile();
    object->setupLeaderboard();
}

static void writeSaveFileTaskEntry(void* arg)
{
    CompFile* object = reinterpret_cast<CompFile*>(arg);
    object->writeSaveTask();
}

static void writeGhostTaskEntry(void* arg)
{
    CompFile* object = reinterpret_cast<CompFile*>(arg);
    object->writeGhostDataTask();
}

void CompFile::switchCompetition(int compId)
{
    if (compId == m_compId)
        return;

    m_compId = compId;
    m_isFileAvailable = false;

    m_thread->request(taskEntry, reinterpret_cast<void*>(this), nullptr);
}

void CompFile::requestWriteSaveFile()
{
    m_saveDataStatus = SAVE_WAITING;
    m_thread->request(writeSaveFileTaskEntry, reinterpret_cast<void*>(this),
                      nullptr);
}

void CompFile::requestSaveGhostData()
{
    m_ghostDataStatus = SAVE_WAITING;

    m_thread->request(writeGhostTaskEntry, reinterpret_cast<void*>(this),
                      nullptr);
}

static bool ldbEntryCompare(CompSaveFile::LdbEntry* entry,
                            GhostData::RaceTime* time)
{
    if (!entry->isEnabled)
        return false;

    if (entry->minutes != time->minutes)
        return entry->minutes < time->minutes;

    if (entry->seconds != time->seconds)
        return entry->seconds < time->seconds;

    if (entry->milliseconds != time->milliseconds)
        return entry->milliseconds < time->milliseconds;

    return true;
}

bool CompFile::shouldGhostSave(GhostData::RaceTime* time)
{
    // Don't allow ghosts to save if the Wii Wheel restriction has been
    // disabled.
    if (m_rkc.objective.forceWiiWheel && m_forceHandleDisabled)
        return false;

    u8 mode = getLicenseSaveData()->ghostSaveMode;

    if (mode == CompSaveFile::Data::GHOST_SAVE_ALL) {
        return true;
    }

    if (mode == CompSaveFile::Data::GHOST_SAVE_BEST_TIME) {
        if (RKContext::sInstance->m_98->m_leaderboardRank == 0)
            return true;
        return false;
    }

    return false;
}

void CompFile::setText(const wchar_t* title, const wchar_t* explanation)
{
    m_compTitle = title;
    m_compExplanation = explanation;
}

int CompFile::getTimeLdbPosition(GhostData::RaceTime* time)
{
    // Don't allow any leaderboard positions if the Wii Wheel restriction has
    // been disabled.
    if (m_rkc.objective.forceWiiWheel && m_forceHandleDisabled)
        return -1;

    for (int i = 0; i < 5; i++) {
        if (!ldbEntryCompare(&m_leaderboard[i], time))
            return i;
    }
    return -1;
}

void CompFile::getLdbEntry(u8 position, LeaderboardEntry* entry)
{
    if (position > 4) {
        entry->time.valid = false;
        return;
    }

    CompSaveFile::LdbEntry* ldb = &m_leaderboard[position];

    memcpy(&entry->mii, &ldb->mii, sizeof(MiiData));

    entry->time.minutes = ldb->minutes;
    entry->time.seconds = ldb->seconds;
    entry->time.milliseconds = ldb->milliseconds;

    entry->characterId = ldb->characterId;
    entry->vehicleId = ldb->vehicleId;
    entry->controllerId = ldb->controllerId;

    entry->time.valid = ldb->isEnabled;
}

void CompFile::insertTimeInLdb(LeaderboardEntry* entry, u32 position)
{
    if (position < 4) {
        memmove(&m_leaderboard[position + 1], &m_leaderboard[position],
                (4 - position) * sizeof(CompSaveFile::LdbEntry));
    }

    CompSaveFile::LdbEntry* ldb = &m_leaderboard[position];

    memcpy(&ldb->mii, &entry->mii, sizeof(MiiData));

    ldb->minutes = entry->time.minutes;
    ldb->seconds = entry->time.seconds;
    ldb->milliseconds = entry->time.milliseconds;

    ldb->characterId = entry->characterId;
    ldb->vehicleId = entry->vehicleId;
    ldb->controllerId = entry->controllerId;

    ldb->isEnabled = entry->time.valid;

    requestWriteSaveFile();
}

struct CompInfo {
    u8 unk_0x0;
    const void* rkcData;
    u32 unk_0x8;
    u32 unk_0xC;
    const wchar_t* titleText;
    u32 titleTextLen;
    u8 unk_0x18;
};

int checkForCompetitionReplace(u8* r3, CompInfo* info)
{
    static wchar_t titleText[64];

    while (!CompFile::sInstance->isFileAvailable()) {
        if (!CompFile::sInstance->isTaskExist())
            return 0;
        // Sleep 16ms
        OSSleepTicks(0xED4E0);
    }

    info->unk_0x0 = 0;
    info->unk_0xC = 1;
    info->unk_0x18 = 1;
    info->unk_0x0 = 1;

    swprintf(titleText, 63, CompFile::sInstance->m_compTitle,
             CompFile::sInstance->m_compId);
    info->titleText = titleText;
    info->titleTextLen = wcslen(titleText);

    info->rkcData = CompFile::sInstance->getData();
    return 1;
}

const wchar_t* getCompetitionTextReplace(u8* r3, u32* len)
{
    return CompFile::sInstance->m_compExplanation;
}

int getTimeLdbPosition(u8* r3, GhostData::RaceTime* time)
{
    return CompFile::sInstance->getTimeLdbPosition(time);
}

void insertTimeInLdb(u8* r3, LeaderboardEntry* entry, int position)
{
    CompFile::sInstance->insertTimeInLdb(entry, position);
}

void getLdbEntry(u8* r3, u8 position, LeaderboardEntry* entry)
{
    CompFile::sInstance->getLdbEntry(position, entry);
}

void makeGhostUserData(wchar_t* userData)
{
    const MenuSet::RaceSetting* set = &MenuSet::sInstance->currentRace;
    u32 count = set->playerCount;

    // Compress the CPU character and vehicle combo into 6 bits for character
    // and 6 for vehicle
    for (int i = 1; i < count; i++) {
        int bit = (i - 1) * 12;
        int index = bit / 16;
        int bitInIndex = bit - index * 16;

        u16 value = (set->players[i].characterId & 0x3F) << 6;
        value |= (set->players[i].vehicleId & 0x3F);
        value <<= 16 - 12;

        userData[index] |= value >> bitInIndex;
        userData[index + 1] |= value << (16 - bitInIndex);
    }

    // And maybe save the random seed?
}

void saveTournamentGhost(u8* r3, int r4, int r5, GhostData* ghost)
{
    if (!isRiivolution())
        return;
    if (!ghost->m_valid)
        return;
    if (!CompFile::sInstance->shouldGhostSave(&ghost->m_finishTime))
        return;

    makeGhostUserData(ghost->m_userData);
    CompFile::sInstance->m_ghost = *ghost; // Copy

    CompFile::sInstance->requestSaveGhostData();
}

// Non-race finish times normally have a 16 ms randomness to them. This patches
// that to always give the best time.
int randomFinishTimeHook(Random* random, int limit)
{
    if (isTournamentMode())
        return 0;

    return random->nextLimited(limit);
}

extern Instruction<1> Patch_Nwc24DlManager_init;
extern Instruction<1> Patch_Nwc24DlManager_CheckForCompetition;
extern Instruction<1> Patch_Nwc24DlManager_GetCompetitionText;
extern Instruction<1> Patch_Nwc24DlManager_GetLdbTimeRank;
extern Instruction<1> Patch_Nwc24DlManager_InsertTimeInLdb;
extern Instruction<1> Patch_Nwc24DlManager_GetLdbEntry;
extern Instruction<1> Patch_SaveTournamentGhost;
extern Instruction<1> Patch_NoRandomFinishTime;
void initCompFilePatches()
{
    Patch_Nwc24DlManager_init.setBlr();
    Patch_Nwc24DlManager_CheckForCompetition.setB(checkForCompetitionReplace);
    Patch_Nwc24DlManager_GetCompetitionText.setB(getCompetitionTextReplace);
    Patch_Nwc24DlManager_GetLdbTimeRank.setB(getTimeLdbPosition);
    Patch_Nwc24DlManager_InsertTimeInLdb.setB(insertTimeInLdb);
    Patch_Nwc24DlManager_GetLdbEntry.setB(getLdbEntry);

    Patch_SaveTournamentGhost.m_instr[0] = 0x60000000;
    Patch_SaveTournamentGhost.setBL(saveTournamentGhost, 0x58 / 4);

    Patch_NoRandomFinishTime.setBL(randomFinishTimeHook);
}