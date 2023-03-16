// patch.h - Tools for patching game code
//
// SPDX-License-Identifier: MIT

#pragma once
#include <rvl/cache.h>
#include <rvl/types.h>

namespace BranchType
{
enum E {
    B,
    BL
};
} // namespace BranchType

template <int N>
struct Instruction {
    void flush()
    {
        const u32 cacheLineAddr = reinterpret_cast<u32>(m_instr) & ~31;
        const u32 cacheLineEnd =
          (reinterpret_cast<u32>(m_instr + N) + 31) & ~31;
        DCFlushRange(reinterpret_cast<void*>(cacheLineAddr),
                     cacheLineEnd - cacheLineAddr);
    }

    template <class T>
    u32 makeBranch(int offset, T* dest, BranchType::E type)
    {
        const u32 destAddr = reinterpret_cast<u32>(dest);

        u32 patch =
          0x48000000 |
          ((destAddr - reinterpret_cast<u32>(&m_instr[offset])) & 0x03FFFFFC);
        if (type == BranchType::BL)
            patch |= 1;

        return patch;
    }

    template <class T>
    void setB(T dest, int offset = 0)
    {
        m_instr[offset] = makeBranch(offset, dest, BranchType::B);
        flush();
    }

    template <class T>
    void setBL(T dest, int offset = 0)
    {
        m_instr[offset] = makeBranch(offset, dest, BranchType::BL);
        flush();
    }

    void setBlr(int offset = 0)
    {
        m_instr[offset] = 0x4E800020;
        flush();
    }

    void setNop(int offset = 0)
    {
        m_instr[offset] = 0x60000000;
        flush();
    }

    u32 m_instr[N];
};
