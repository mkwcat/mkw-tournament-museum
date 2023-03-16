// ipc.h
//
// SPDX-License-Identifier: MIT

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
