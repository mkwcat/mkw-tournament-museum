// loader.cpp - Custom REL loader for Mario Kart Wii
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

#include <egg/eggDvdFile.h>
#include <egg/eggHeap.h>
#include <rvl/types.h>

#define assert(expr)                                                           \
    (((expr) ? (void)0 : __assert_fail(#expr, __FILE__, __LINE__)))

static void loaderMain(void* rel, void* bss, EGG::Heap* heap);
static void relCallProlog(void* rel);
static void relCallEpilog(void* rel);
static void* loadCustomModule(EGG::Heap* heap);
static void* loadFromDVD(EGG::Heap* heap, s32 entryNum);
static void* loadFromNAND(EGG::Heap* heap, s32 fd);
static void __assert_fail(const char* expr, const char* file, s32 line);

EXTERN_C_START

asm bool __start()
{
    // clang-format off
    nofralloc
    mflr    r26

    // r3 = module, r4 = bss
    mr      r5, r24 // heap
    bl      loaderMain

    li      r3, 1
    mtlr    r26
    blr
    // clang-format on
}

// hack delete unneeded vtable
asm void __vt__Q23EGG7DvdFile()
{
}

EXTERN_C_END

s32 rmc_index = -1;

#define DEFINE_EXTERNAL_FUNCTION(_definition, _addr_e, _addr_j, _addr_p,       \
                                 _addr_k)                                      \
    asm _definition                                                            \
    {                                                                          \
        nofralloc;                                                             \
        mflr r12;                                                              \
        bl port_call;                                                          \
        opword _addr_e;                                                        \
        opword _addr_j;                                                        \
        opword _addr_p;                                                        \
        opword _addr_k;                                                        \
    }

static asm void port_call()
{
    // clang-format off
    nofralloc
    mflr    r11
    mtlr    r12
    lis     r12, rmc_index@ha
    lwz     r12, rmc_index@l(r12)
    rlwinm  r12, r12, 2, 0, 29
    lwzx    r12, r11, r12
    mtctr   r12
    bctr
    // clang-format on
}

// clang-format off

EXTERN_C_START
DEFINE_EXTERNAL_FUNCTION(
    int snprintf(char* str, u32 n, const char* format, ...),
    0x80010DD8, 0x8001185C, 0x80011938, 0x800119A0
)
DEFINE_EXTERNAL_FUNCTION(
    s32 IOS_Open(const char* path, u32 mode),
    0x80193858, 0x80193818, 0x801938F8, 0x80193C54
)
DEFINE_EXTERNAL_FUNCTION(
    s32 IOS_Close(s32 fd),
    0x80193A38, 0x801939F8, 0x80193AD8, 0x80193E34
)
DEFINE_EXTERNAL_FUNCTION(
    s32 IOS_Seek(s32 fd, s32 where, s32 whence),
    0x80193FD0, 0x80193F90, 0x80194070, 0x801943CC
)
DEFINE_EXTERNAL_FUNCTION(
    s32 IOS_Read(s32 fd, void* data, u32 len),
    0x80193BE0, 0x80193BA0, 0x80193C80, 0x80193FDC
)
DEFINE_EXTERNAL_FUNCTION(
    void OSReport(const char* format, ...),
    0x801A2530, 0x801A24F0, 0x801A25D0, 0x801A292C
)
DEFINE_EXTERNAL_FUNCTION(
    bool OSLink(void* rel, void* bss),
    0x801A723C, 0x801A71FC, 0x801A72DC, 0x801A7638
)
DEFINE_EXTERNAL_FUNCTION(
    s32 DVDConvertPathToEntrynum(const char* path),
    0x8015DEAC, 0x8015DE6C, 0x8015DF4C, 0x8015DFC4
)
EXTERN_C_END

// Can't do constructors!
// Error:
// (10424) internal compiler error (report to <cw_bug@freescale.com>)
// while executing in file 'CMiddleLayer.c' line: 1085
// (compiling '__ct__Q23EGG7DvdFileFv' in 'main.cpp')
DEFINE_EXTERNAL_FUNCTION(
    EGG::DvdFile makeDvdFile(),
    0x802222BC, 0x8022227C, 0x8022235C, 0x802226D0
)
DEFINE_EXTERNAL_FUNCTION(
    EGG::DvdFile::~DvdFile(),
    0x80222300, 0x802222C0, 0x802223A0, 0x80222714
)
DEFINE_EXTERNAL_FUNCTION(
    bool EGG::DvdFile::open(s32 entryNum),
    0x802223D0, 0x80222390, 0x80222470, 0x802227E4
)
DEFINE_EXTERNAL_FUNCTION(
    bool EGG::DvdFile::open(const char* path),
    0x80222448, 0x80222408, 0x802224E8, 0x8022285C
)
DEFINE_EXTERNAL_FUNCTION(
    bool EGG::DvdFile::open(const char* path, void*),
    0x80222490, 0x80222450, 0x80222530, 0x802228A4
)
DEFINE_EXTERNAL_FUNCTION(
    void EGG::DvdFile::close(),
    0x802224A0, 0x80222460, 0x80222540, 0x802228B4
)
DEFINE_EXTERNAL_FUNCTION(
    s32 EGG::DvdFile::readData(void* data, s32 len, s32 offset),
    0x802224FC, 0x802224BC, 0x8022259C, 0x80222910
)
DEFINE_EXTERNAL_FUNCTION(
    s32 EGG::DvdFile::writeData(const void* data, s32 len, s32 offset),
    0x802225C0, 0x80222580, 0x80222660, 0x802229D4
)
DEFINE_EXTERNAL_FUNCTION(
    s32 EGG::DvdFile::getFileSize() const,
    0x80222630, 0x802225F0, 0x802226D0, 0x80222A44
)

// clang-format on

static inline u32 relBssSize(void* rel)
{
    return reinterpret_cast<u32*>(rel)[0x20 >> 2];
}

static void loaderMain(void* rel, void* bss, EGG::Heap* heap)
{
    char region = *reinterpret_cast<char*>(0x80000003);
    rmc_index = region == 'E'   ? 0
                : region == 'J' ? 1
                : region == 'P' ? 2
                : region == 'K' ? 3
                                : -1;
    assert(rmc_index != -1);

    bool ret = OSLink(rel, bss);
    assert(ret);

    void* new_rel = loadCustomModule(heap);
    assert(new_rel);

    void* new_bss = heap->alloc(relBssSize(new_rel), 32);
    assert(new_bss);

    ret = OSLink(new_rel, new_bss);
    assert(ret);
    relCallProlog(new_rel);
}

static asm void relCallProlog(register void* rel)
{
    // clang-format off
    lwz     r12, 0x34(rel)
    mtctr   r12
    bctr
    // clang-format on
}

static asm void relCallEpilog(register void* rel)
{
    // clang-format off
    lwz     r12, 0x38(rel)
    mtctr   r12
    bctr
    // clang-format on
}

static bool isDolphin()
{
    // Check for /dev/dolphin
    s32 fd = IOS_Open("/dev/dolphin", 0);
    if (fd >= 0) {
        IOS_Close(fd);
        return true;
    }
    // Or on an older version of dolphin, this bug will work.
    if (fd = IOS_Open("/title", 1) == -106) {
        return true;
    }

    if (fd >= 0) {
        IOS_Close(fd);
    }
    return false;
}

static void* loadCustomModule(EGG::Heap* heap)
{
    char relPath[64];

    snprintf(relPath, 64, "/rel/mkwtm_%c.rel",
             *reinterpret_cast<char*>(0x80000003));

    const s32 entryNum = DVDConvertPathToEntrynum(relPath);

    if (entryNum != -1) {
        return loadFromDVD(heap, entryNum);
    }

    return 0;
}

static void* loadFromDVD(EGG::Heap* heap, s32 entryNum)
{
    EGG::DvdFile file = makeDvdFile();
    bool ret = file.open(entryNum);
    assert(ret);

    void* data = heap->alloc((file.getFileSize() + 31) & ~31, 32);
    assert(data != 0);

    ret = file.readData(data, file.getFileSize(), 0) != -1;
    assert(ret);

    file.close();
    return data;
}

static void* loadFromNAND(EGG::Heap* heap, s32 fd)
{
    const s32 size = IOS_Seek(fd, 0, 2 /* IOS_SEEK_END */);
    assert(size > 0);
    s32 ret = IOS_Seek(fd, 0, 0 /* IOS_SEEK_SET */);
    assert(ret == 0);

    void* data = heap->alloc((size + 31) & ~31, 32);
    assert(data != 0);

    ret = IOS_Read(fd, data, size);
    assert(ret == size);
    return data;
}

void __assert_fail(const char* expr, const char* file, s32 line)
{
    OSReport("mkwtm loader assertion failed\n"
             "  %s\n"
             "  at file %s, line %d\n",
             expr, file, line);
    while (1) {
    }
}
