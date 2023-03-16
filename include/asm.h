// asm.h
//
// SPDX-License-Identifier: MIT

#pragma once

#ifdef __clang__

#  define CR0 0
#  define CR1 1
#  define CR2 2
#  define CR3 3
#  define CR4 4
#  define CR5 5
#  define CR6 6
#  define CR7 7

// clang-format off

#  define R0 %r0
#  define R1 %r1
#  define SP %r1
#  define R2 %r2
#  define TOC %r2
#  define R3 %r3
#  define R4 %r4
#  define R5 %r5
#  define R6 %r6
#  define R7 %r7
#  define R8 %r8
#  define R9 %r9
#  define R10 %r10
#  define R11 %r11
#  define R12 %r12
#  define R13 %r13
#  define R14 %r14
#  define R15 %r15
#  define R16 %r16
#  define R17 %r17
#  define R18 %r18
#  define R19 %r19
#  define R20 %r20
#  define R21 %r21
#  define R22 %r22
#  define R23 %r23
#  define R24 %r24
#  define R25 %r25
#  define R26 %r26
#  define R27 %r27
#  define R28 %r28
#  define R29 %r29
#  define R30 %r30
#  define R31 %r31

// clang-format on

#  define F0 0
#  define F1 1
#  define F2 2
#  define F3 3
#  define F4 4
#  define F5 5
#  define F6 6
#  define F7 7
#  define F8 8
#  define F9 9
#  define F10 10
#  define F11 11
#  define F12 12
#  define F13 13
#  define F14 14
#  define F15 15
#  define F16 16
#  define F17 17
#  define F18 18
#  define F19 19
#  define F20 20
#  define F21 21
#  define F22 22
#  define F23 23
#  define F24 24
#  define F25 25
#  define F26 26
#  define F27 27
#  define F28 28
#  define F29 29
#  define F30 30
#  define F31 31

#  define ASM(...) asm(#__VA_ARGS__)

#  define ASM_FUNCTION(_PROTOTYPE, ...)                                        \
    __attribute__((naked)) _PROTOTYPE                                          \
    {                                                                          \
      ASM(__VA_ARGS__);                                                        \
    }

#else

#  define CR0 cr0
#  define CR1 cr1
#  define CR2 cr2
#  define CR3 cr3
#  define CR4 cr4
#  define CR5 cr5
#  define CR6 cr6
#  define CR7 cr7

#  define R0 r0
#  define R1 r1
#  define SP r1
#  define R2 r2
#  define TOC r2
#  define R3 r3
#  define R4 r4
#  define R5 r5
#  define R6 r6
#  define R7 r7
#  define R8 r8
#  define R9 r9
#  define R10 r10
#  define R11 r11
#  define R12 r12
#  define R13 r13
#  define R14 r14
#  define R15 r15
#  define R16 r16
#  define R17 r17
#  define R18 r18
#  define R19 r19
#  define R20 r20
#  define R21 r21
#  define R22 r22
#  define R23 r23
#  define R24 r24
#  define R25 r25
#  define R26 r26
#  define R27 r27
#  define R28 r28
#  define R29 r29
#  define R30 r30
#  define R31 r31

#  define F0 f0
#  define F1 f1
#  define F2 f2
#  define F3 f3
#  define F4 f4
#  define F5 f5
#  define F6 f6
#  define F7 f7
#  define F8 f8
#  define F9 f9
#  define F10 f10
#  define F11 f11
#  define F12 f12
#  define F13 f13
#  define F14 f14
#  define F15 f15
#  define F16 f16
#  define F17 f17
#  define F18 f18
#  define F19 f19
#  define F20 f20
#  define F21 f21
#  define F22 f22
#  define F23 f23
#  define F24 f24
#  define F25 f25
#  define F26 f26
#  define F27 f27
#  define F28 f28
#  define F29 f29
#  define F30 f30
#  define F31 f31

#  define ASM_FUNCTION(_PROTOTYPE, ...)                                        \
    asm _PROTOTYPE                                                             \
    {                                                                          \
      nofralloc;                                                               \
      __VA_ARGS__                                                              \
    }

#endif
