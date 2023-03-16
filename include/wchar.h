// wchar.h
//
// SPDX-License-Identifier: MIT

#pragma once
#include <rvl/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 0x80017814 */
int swprintf(wchar_t* str, size_t num, const wchar_t* format, ...);

/* 0x80017998 */
size_t wcslen(wchar_t* str);

#ifdef __cplusplus
}
#endif
