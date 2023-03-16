// stdio.h
//
// SPDX-License-Identifier: MIT

#pragma once
#include <rvl/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 0x800116E4 */
int printf(const char* format, ...);

/* 0x80011938 */
int snprintf(char* str, size_t num, const char* format, ...);

/* 0x80011A2C */
int sprintf(char* str, const char* format, ...);

#ifdef __cplusplus
}
#endif
