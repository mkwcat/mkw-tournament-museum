// MsgRes.h - BMG file reader
//
// SPDX-License-Identifier: MIT

#pragma once
#include <rvl/types.h>

namespace UI
{

class MsgRes
{
public:
    struct FormatParam {
        s32 intVals[9];
        u32 messageIds[9];
        const void* miis[9];
        u8 licenseIds[9];
        u32 playerIds[9];
        const wchar_t* strings[9];
        u32 unk_0xC0;
    };

    void* m_data;
    void* m_inf1;
    void* m_dat1;
    void* m_str1;
    void* m_mid1;

    int getIndexFromMid(int mid) const;
    wchar_t* getTextFromIndex(int index) const;
};

static_assert(sizeof(MsgRes) == 0x14, "sizeof(MsgRes) != 0x14");

} // namespace UI
