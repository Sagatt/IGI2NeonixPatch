#pragma once

namespace Utils
{
    IGI_INLINE bool CutScene_IsRunning()
    {
        return *reinterpret_cast<bool*>(0x743F0C);
    }

    IGI_INLINE void __fastcall Flow_SetFrequency(int frequency)
    {
        __asm
        {
            mov esi, frequency
            mov ecx, 0x402CA0
            call ecx
        }
    }

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