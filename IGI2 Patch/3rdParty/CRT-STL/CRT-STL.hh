#pragma once

//------------------------------------------------------------------------------------------
// 
//  - Only Clang (LLVM) + Windows, fuck MSVC.
// 
//  - Include this file only in main file that has entrypoint.
// 
//  - If there is requirement to implement some STL function, then first 
//    include the required header file that contain the function and
//    then make own implementation that will get "forwarded" to.
// 
//  - Inside entrypoint call "CRT::Initialize" to call C/C++ constructors.
// 
//------------------------------------------------------------------------------------------

//=======================================================================
// Macros / Pre-processors

#define CRT_INLINE      __forceinline
#define STL_INLINE      __forceinline

//=======================================================================
// Includes (Default)

#define _CORECRT_BUILD // Remove __declspec(dllimport)
#include <Windows.h>
#include <intrin.h> // __fastfail

// Memory Manager (Required)
#include "MemoryMgr.hh"

//=======================================================================
// Includes (STL)

#include "STL/string.hh"
#include "STL/xutility.hh"

//=======================================================================
// Externs

extern "C"
{
    int _fltused = 0;

    void exit(int _Code)
    {
        __fastfail(_Code);
    }
}


//=======================================================================
// C++ Runtime Stuff
// https://wiki.osdev.org/Visual_C++_Runtime

typedef void(__cdecl* _PVFV)(void);
typedef int(__cdecl* _PIFV)(void);

// Linker puts constructors between these sections, and we use them to locate constructor pointers.
#pragma section(".CRT$XIA",long,read)
#pragma section(".CRT$XIZ",long,read)
#pragma section(".CRT$XCA",long,read)
#pragma section(".CRT$XCZ",long,read)

// Put .CRT data into .rdata section
#pragma comment(linker, "/merge:.CRT=.rdata")

__declspec(allocate(".CRT$XIA")) _PIFV __xi_a[] = { 0 };
__declspec(allocate(".CRT$XIZ")) _PIFV __xi_z[] = { 0 };
__declspec(allocate(".CRT$XCA")) _PVFV __xc_a[] = { 0 };
__declspec(allocate(".CRT$XCZ")) _PVFV __xc_z[] = { 0 };

extern __declspec(allocate(".CRT$XIA")) _PIFV __xi_a[];
extern __declspec(allocate(".CRT$XIZ")) _PIFV __xi_z[];
extern __declspec(allocate(".CRT$XCA")) _PVFV __xc_a[];
extern __declspec(allocate(".CRT$XCZ")) _PVFV __xc_z[];

// Call C constructors
int _initterm_e(_PIFV* pfbegin, _PIFV* pfend)
{
    int ret = 0;

    while (pfbegin < pfend && ret == 0)
    {
        if (*pfbegin != 0) {
            ret = (**pfbegin)();
        }
        ++pfbegin;
    }

    return ret;
}

// Call C++ constructors
void _initterm(_PVFV* pfbegin, _PVFV* pfend)
{
    while (pfbegin < pfend)
    {
        if (*pfbegin != 0) {
            (**pfbegin)();
        }
        ++pfbegin;
    }
}

namespace CRT
{
    bool Initialize()
    {
        // Do C initialization
        if (_initterm_e(__xi_a, __xi_z) != 0) {
            return false;
        }

        // Do C++ initialization
        _initterm(__xc_a, __xc_z);
        return true;
    }
}