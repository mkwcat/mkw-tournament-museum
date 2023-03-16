// dvd.h
//
// SPDX-License-Identifier: MIT

#pragma once
#include <rvl/types.h>

EXTERN_C_START

typedef struct {
    u8 fill[0x30];
    u32 wordOffset;
    u32 byteLength;
    u8 fill2[4];
} DVDFileInfo;

EXTERN_C_END
