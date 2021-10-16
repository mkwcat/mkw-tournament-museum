// File.cpp - NAND / Riivo file I/O
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

#include "File.h"
#include <rvl/ipc.h>
#include <stdio.h>
#include <string.h>

RiivoFS* RiivoFS::sInstance;

static s32 nandToFSError(s32 error)
{
    if (error >= 0)
        return FSError::OK;

    switch (error) {
    case NAND_CODE_NOT_EXIST:
        return FSError::FILE_NOT_FOUND;

    default:
        return FSError::OTHER;
    }
}

NandFile::NandFile()
{
    m_error = NAND_CODE_OK;
    m_length = 0;
}

NandFile::~NandFile()
{
}

bool NandFile::open(const char* path)
{
    return open(path, NAND_MODE_READ);
}

bool NandFile::open(const char* path, u8 mode)
{
    m_error = NANDOpen(path, &m_file, mode);

    if (m_error != NAND_CODE_OK)
        return false;

    NANDGetLength(&m_file, &m_length);
    return true;
}

bool NandFile::openCreate(const char* path, u8 mode)
{
    if (!(mode & NAND_MODE_WRITE))
        return false;

    bool ret = open(path, mode);

    if (ret == true)
        return true;
    if (m_error != NAND_CODE_NOT_EXIST)
        return false;

    m_error = NANDCreate(path, NAND_PERM_READ_WRITE, 0);

    if (m_error != NAND_CODE_OK)
        return false;

    return open(path, mode);
}

void NandFile::close()
{
    NANDClose(&m_file);
    m_error = NAND_CODE_OK;
    m_length = 0;
}

s32 NandFile::readData(void* data, s32 len, s32 offset)
{
    if (offset != -1) {
        s32 ret = NANDSeek(&m_file, offset, NAND_SEEK_SET);

        if (ret != offset)
            return -1;
    }

    s32 ret = NANDRead(&m_file, data, len);

    if (ret != len)
        return -1;

    return ret;
}

s32 NandFile::writeData(const void* data, s32 len, s32 offset)
{
    if (offset != -1) {
        s32 ret = NANDSeek(&m_file, offset, NAND_SEEK_SET);

        if (ret != offset)
            return -1;
    }

    s32 ret = NANDWrite(&m_file, data, len);

    if (ret != len)
        return -1;

    return ret;
}

s32 NandFile::getFileSize() const
{
    return m_length;
}

s32 NandFile::getFSError()
{
    return nandToFSError(m_error);
}

RiivoFile::RiivoFile()
{
    m_fd = -1;
}

RiivoFile::~RiivoFile()
{
}

static u32 nandToRiivoMode(u8 mode)
{
    return (mode & NAND_MODE_RW) - 1;
}

static s32 riivoToFSError(s32 error)
{
    if (error >= 0)
        return FSError::OK;

    switch (error) {
    default:
        return FSError::OTHER;
    }
}

bool RiivoFile::openLow(const char* path, u32 mode)
{
    m_error = IOS_Open(path, mode);

    if (m_error < 0)
        return false;
    m_fd = m_error;

    m_length = IOS_Seek(m_fd, 0, IOS_SEEK_END);
    IOS_Seek(m_fd, 0, IOS_SEEK_SET);

    return true;
}

bool RiivoFile::openInternal(const char* path, u32 mode)
{
    // IOS max path length is 63 characters. Since 64 isn't enough for many
    // cases, Riivolution implements a 'shorten path' ioctl.
    if (strlen(path) + 4 > IPC_MAX_PATH) {
        // This is not threadsafe!
        static char fpath[RIIVO_MAX_PATH];
        static char shortPath[RIIVO_SHORT_PATH_LEN];

        snprintf(fpath, RIIVO_MAX_PATH, "file/%s", path);
        RiivoFS::sInstance->getShortPath(fpath, shortPath);

        return openLow(shortPath, mode);
    }

    // For normal IPC length paths
    char fpath[IPC_MAX_PATH];

    snprintf(fpath, IPC_MAX_PATH, "file/%s", path);

    return openLow(fpath, mode);
}

bool RiivoFile::open(const char* path, u8 mode)
{
    bool ret = openInternal(path, nandToRiivoMode(mode));

    if (!ret)
        return false;

    return true;
}

bool RiivoFile::openCreate(const char* path, u8 mode)
{
    if (!(mode & NAND_MODE_WRITE))
        return false;

    bool ret = openInternal(path, nandToRiivoMode(mode) | 0x600);

    if (!ret)
        return false;

    return true;
}

void RiivoFile::close()
{
    IOS_Close(m_fd);
    m_fd = -1;
    m_error = 0;
}

s32 RiivoFile::readData(void* data, s32 len, s32 offset)
{
    if (offset != -1) {
        s32 ret = IOS_Seek(m_fd, offset, IOS_SEEK_SET);

        if (ret != offset)
            return -1;
    }

    s32 ret = IOS_Read(m_fd, data, len);

    if (ret != len)
        return -1;

    return ret;
}

s32 RiivoFile::writeData(const void* data, s32 len, s32 offset)
{
    if (offset != -1) {
        s32 ret = IOS_Seek(m_fd, offset, IOS_SEEK_SET);

        if (ret != offset)
            return -1;
    }

    s32 ret = IOS_Write(m_fd, data, len);

    if (ret != len)
        return -1;

    return ret;
}

s32 RiivoFile::getFileSize() const
{
    return m_length;
}

s32 RiivoFile::getFSError()
{
    return riivoToFSError(m_error);
}

void RiivoFS::initialize()
{
    sInstance = new RiivoFS();
}

RiivoFS::RiivoFS()
{
    m_fd = IOS_Open("file", IOS_OPEN_NONE);
}

RiivoFS::~RiivoFS()
{
}

void RiivoFS::getShortPath(const char* inPath, char* out)
{
    IOS_Ioctl(m_fd, IOCTL_Shorten, reinterpret_cast<const void*>(inPath),
              RIIVO_MAX_PATH, reinterpret_cast<void*>(out),
              RIIVO_SHORT_PATH_LEN);
}

bool RiivoFS::dirExists(const char* path)
{
    s32 ret =
        IOS_Ioctl(m_fd, IOCTL_OpenDir, reinterpret_cast<const void*>(path),
                  strlen(path) + 1, nullptr, 0);
    if (ret >= 0) {
        IOS_Ioctl(m_fd, IOCTL_CloseDir, reinterpret_cast<const void*>(&ret),
                  sizeof(ret), nullptr, 0);
        return true;
    }
    return false;
}

s32 RiivoFS::createDir(const char* path)
{
    return IOS_Ioctl(m_fd, IOCTL_CreateDir, reinterpret_cast<const void*>(path),
                     strlen(path) + 1, nullptr, 0);
}