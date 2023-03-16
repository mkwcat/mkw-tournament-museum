// os.h
//
// SPDX-License-Identifier: MIT

#pragma once
#include <rvl/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void OSSleepTicks(u64 ticks);
void OSReport(const char* format, ...);
void OSFatal(u32* textColor, u32* bgColor, const char* text);

#ifdef __cplusplus
}
#endif
