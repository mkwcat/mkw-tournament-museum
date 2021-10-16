// eggDvdFile.h - DVD file I/O
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