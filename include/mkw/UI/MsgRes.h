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
    // This is probably not here
    struct FormatParam {
        int intParam;
        int intParam2;
        u8 fill[0xC0];
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
