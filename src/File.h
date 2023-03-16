// File.h - NAND / Riivo file I/O
//
// SPDX-License-Identifier: MIT

#pragma once
#include <egg/eggFile.h>
#include <rvl/nand.h>
#include <rvl/types.h>

namespace FSType
{
enum {
    SAVE_NAND,
    SAVE_RIIVO
};
} // namespace FSType

namespace FSError
{
enum {
    OK,
    FILE_NOT_FOUND,
    NO_ACCESS,
    OTHER,
};
} // namespace FSError

class NandFile : public EGG::File
{
public:
    NandFile();
    virtual ~NandFile();

    bool open(const char* path);
    virtual bool open(const char* path, u8 mode);
    virtual bool openCreate(const char* path, u8 mode);
    virtual void close();
    virtual s32 readData(void* data, s32 len, s32 offset);
    virtual s32 writeData(const void* data, s32 len, s32 offset);
    virtual s32 getFileSize() const;

    virtual s32 getFSError();

protected:
    s32 m_error;
    NANDFileInfo m_file;
    u32 m_length;
};

class RiivoFile : public NandFile
{
public:
    RiivoFile();
    virtual ~RiivoFile();

private:
    bool openLow(const char* path, u32 mode);
    bool openInternal(const char* path, u32 mode);

public:
    virtual bool open(const char* path, u8 mode);
    virtual bool openCreate(const char* path, u8 mode);
    virtual void close();
    virtual s32 readData(void* data, s32 len, s32 offset);
    virtual s32 writeData(const void* data, s32 len, s32 offset);
    virtual s32 getFileSize() const;

    virtual s32 getFSError();

protected:
    s32 m_error;
    s32 m_fd;
};

#define RIIVO_MAX_PATH 1024
#define RIIVO_SHORT_PATH_LEN 32

class RiivoFS
{
public:
    static RiivoFS* sInstance;
    static void initialize();

    enum Ioctl {
        IOCTL_CreateDir = 0x50,
        IOCTL_OpenDir = 0x51,
        IOCTL_CloseDir = 0x53,
        IOCTL_Shorten = 0x60,
        IOCTL_SetSlotLED = 0x65
    };

    RiivoFS();
    virtual ~RiivoFS();

    void getShortPath(const char* inPath, char* out);
    void setSlotLED(bool lit);
    s32 createDir(const char* path);
    bool dirExists(const char* path);

    s32 m_fd;
};
