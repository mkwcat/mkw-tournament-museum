// patch.h - Tools for patching game code
//
// Copyright (c) 2021 TheLordScruffy
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once
#include <rvl/cache.h>
#include <rvl/types.h>

namespace BranchType
{
enum E
{
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