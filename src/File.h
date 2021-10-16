// File.h - NAND / Riivo file I/O
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
#include <egg/eggFile.h>
#include <rvl/nand.h>
#include <rvl/types.h>

namespace FSType
{
enum
{
    SAVE_NAND,
    SAVE_RIIVO
};
} // namespace FSType

namespace FSError
{
enum
{
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

    enum Ioctl
    {
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