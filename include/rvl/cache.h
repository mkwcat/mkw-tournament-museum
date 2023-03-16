// cache.h
//
// SPDX-License-Identifier: MIT

#pragma once
#include <rvl/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void DCFlushRange(const void* data, u32 length);

#ifdef __cplusplus
}
#endif
