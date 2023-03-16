// eggFile.h - File I/O
//
// SPDX-License-Identifier: MIT

#pragma once
#include <rvl/types.h>

namespace EGG
{

class File
{
public:
    virtual ~File()
    {
    }

    virtual bool open(const char* path) = 0;
    virtual void close() = 0;
    virtual s32 readData(void* data, s32, s32) = 0;
    virtual s32 writeData(const void* data, s32, s32) = 0;
    virtual s32 getFileSize() const = 0;
};

} // namespace EGG
