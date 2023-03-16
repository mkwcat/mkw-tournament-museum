// eggHeap.h
//
// SPDX-License-Identifier: MIT

#pragma once
#include <egg/eggDisposer.h>
#include <rvl/types.h>

namespace EGG
{

class Heap : public Disposer
{
public:
    virtual ~Heap();
    /* Not included */
    virtual s32 _0(); // getHeapKind
    virtual s32 _1(); // initAllocator
    virtual void* alloc(u32 len, s32 align) = 0;
    virtual void free(void* block) = 0;
    /* Not included */
    virtual s32 _2(); // destroy
    virtual s32 _3(); // resizeForMBlock
    virtual s32 _4(); // getAllocatableSize
    virtual s32 _5(); // adjust

    /* Data not included */
};

} // namespace EGG
