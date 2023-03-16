// eggDvdFile.h - DVD file I/O
//
// SPDX-License-Identifier: MIT

#pragma once
#include "eggFile.h"
#include <rvl/dvd.h>
#include <rvl/types.h>

namespace EGG
{

class DvdFile : public File
{
public:
    DvdFile();
    virtual ~DvdFile();

    virtual bool open(s32 entryNum);
    virtual bool open(const char* path);
    virtual bool open(const char* path, void*);
    virtual void close();
    virtual s32 readData(void* data, s32 len, s32 offset);
    virtual s32 writeData(const void* data, s32 len, s32 offset);
    virtual s32 getFileSize() const;

public:
    bool m_isOpen; // [0x4]
private:
    u32 m_fill[0x30 >> 2];
    int m_0x38;

public:
    DVDFileInfo m_fileInfo; // [0x3C]
    DvdFile* m_dvdFile; // [0x78] pointer to itself?
private:
    u8 m_fill2[0x76];
};

} // namespace EGG
