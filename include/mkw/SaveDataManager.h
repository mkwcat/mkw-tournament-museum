// SaveDataManager.h - Handles rksys.dat and other save data probably
//
// SPDX-License-Identifier: MIT

#pragma once
#include "GhostData.h"
#include <rvl/types.h>

class SaveDataManager
{
public:
    static SaveDataManager* sInstance;
    SaveDataManager();
    ~SaveDataManager();

    u8 fill[0x14];
    void* m_rksys;
    GhostData::RKGFile* m_rkgFile;
    u8 fill2[0x28008 - 0x1C];
};
