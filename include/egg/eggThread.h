// eggThread.h
//
// SPDX-License-Identifier: MIT

#pragma once
#include "eggHeap.h"
#include <rvl/types.h>

namespace EGG
{

class Thread
{
public:
    Thread(u32 stackSize, int msgCount, int priority, Heap* heap);
    virtual ~Thread();

    virtual void* run();
    virtual void onEnter();
    virtual void onExit();

    u8 fill[0x40];
};

static_assert(sizeof(Thread) == 0x44, "sizeof(Thread) != 0x44");

} // namespace EGG
