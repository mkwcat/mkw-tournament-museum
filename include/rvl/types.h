// types.h
//
// SPDX-License-Identifier: MIT

#pragma once

typedef int BOOL;

typedef char s8;
typedef short s16;
typedef long s32;
typedef long long s64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

typedef u32 size_t;

#ifdef __cplusplus
#  define EXTERN_C_START extern "C" {
#  define EXTERN_C_END }
#else
#  define EXTERN_C_START
#  define EXTERN_C_END
#endif

#define ATTRIBUTE_ALIGN(align) __attribute__((aligned(align)))
