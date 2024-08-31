#pragma once

namespace Utils
{
    IGI_INLINE void* HumanPlayer_Get()
    {
        return *reinterpret_cast<void**>(0x836889C);
    }

    IGI_INLINE bool Game_IsPaused()
    {
        return reinterpret_cast<bool(*)()>(0x40A020)();
    }

    void __fastcall QCamera_InitCurrent()
    {
        __asm
        {
            mov eax, dword ptr[0x83685EC]
            add eax, 0x80

            mov ecx, 0x575E60
            call ecx
        }
    }
}