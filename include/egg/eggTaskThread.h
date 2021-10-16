// eggTaskThread.h
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