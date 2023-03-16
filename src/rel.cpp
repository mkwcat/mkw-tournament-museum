// rel.cpp - REL init
//
// SPDX-License-Identifier: MIT

extern "C" {

typedef void (*PFN_voidfunc)();
__attribute__((section(".ctors"))) extern PFN_voidfunc _ctors[];
__attribute__((section(".ctors"))) extern PFN_voidfunc _ctors_end[];

void _prolog();
void _epilog();
void _unresolved();
}

void MKWTMMain();

__declspec(noinline) void _prolog()
{
    // Run global constructors
    for (PFN_voidfunc* ctor = _ctors; ctor != _ctors_end && *ctor; ++ctor) {
        (*ctor)();
    }

    // Run main
    MKWTMMain();
}

__declspec(noinline) void _epilog()
{
    // Infinite loop
    _epilog();
}

__declspec(noinline) void _unresolved()
{
    // Infinite loop
    _unresolved();
}

#ifdef __clang__
int __dso_handle;

extern "C" void __cxa_atexit()
{
}
#endif
