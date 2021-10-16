// ipc.h
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
#include <rvl/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IOS_SEEK_SET 0
#define IOS_SEEK_CUR 1
#define IOS_SEEK_END 2

#define IOS_OPEN_NONE 0
#define IOS_OPEN_READ 1

#define IPC_MAX_PATH 63

typedef struct {
    void* data;
    u32 len;
} IOSVector;

s32 IOS_Open(const char* path, u32 flags);
s32 IOS_Close(s32 fd);
s32 IOS_Read(s32 fd, void* data, u32 len);
s32 IOS_Write(s32 fd, const void* data, u32 len);
s32 IOS_Seek(s32 fd, s32 offset, s32 origin);
s32 IOS_Ioctl(s32 fd, u32 cmd, const void* in, u32 inLen, void* out,
              u32 outLen);
s32 IOS_Ioctlv(s32 fd, u32 cmd, u32 inCount, u32 outCount, IOSVector* vec);

#ifdef __cplusplus
}
#endif