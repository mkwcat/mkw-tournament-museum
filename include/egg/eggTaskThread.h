// eggTaskThread.h
//
// SPDX-License-Identifier: MIT

#pragma once
#include "eggThread.h"
#include <rvl/types.h>

namespace EGG
{

class TaskThread : public Thread
{
public:
    TaskThread(int msgCount, int priority, u32 stackSize);
    ~TaskThread();

    void* run();
    void onEnter();
    void onExit();

    typedef void (*Proc)(void*);

    static TaskThread* create(int msgCount, int priority, u32 stackSize,
                              Heap* heap);

    bool request(Proc proc, void* arg, void*);
    bool isTaskExist() const;

    u8 fill[0x14];
};

static_assert(sizeof(TaskThread) == 0x58, "sizeof(TaskThread) != 0x58");

} // namespace EGG
