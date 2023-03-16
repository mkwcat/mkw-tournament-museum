// string.h
//
// SPDX-License-Identifier: MIT

#pragma once
#include <rvl/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 0x8001329C */
int strcmp(const char* s1, const char* s2);
/* 0x80021254 */
size_t strlen(const char* str);

/* 0x80005F34 */
void* memcpy(void* dest, const void* src, size_t len);
/* 0x80006038 */
void* memset(void* dest, int c, size_t len);
/* 0x8000F1F0 */
void* memmove(void* dest, const void* src, size_t len);

#ifdef __cplusplus
}
#endif
