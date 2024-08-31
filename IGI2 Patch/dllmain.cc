//==========================================================================
// Includes

#include "Includes.hh"
#include "3rdParty/CRT-STL/CRT-STL.hh"

namespace Helper
{
    void HumanPlayer_ResetAngleInput()
    {
        uintptr_t pHumanPlayer = reinterpret_cast<uintptr_t>(Utils::HumanPlayer_Get());
        if (!pHumanPlayer) {
            return;
        }

        int* pInput = reinterpret_cast<int*>(pHumanPlayer + 0x304);
        pInput[0] = pInput[1] = pInput[2] = 0;
    }
}

namespace Hooks
{
    int __stdcall AppContext_SetInactive()
    {
        // Reset alt key to prevent pressing ALT + Enter that toggles fullscreen mode.
        *reinterpret_cast<bool*>(0x757BD0) = false;
        *reinterpret_cast<bool*>(0x83685E0) = false;

        Helper::HumanPlayer_ResetAngleInput();

        // Reset Mouse Analog X, Y
        __asm
        {
            xor eax, eax

            mov ecx, 0x85402F4
            mov [ecx], eax
            mov [ecx + 0x4], eax
        }

        return 1;
    }

    void __cdecl Direct3D_SwapBuffers()
    {
        reinterpret_cast<void(__cdecl*)()>(0x44AB40)();

        static ULONGLONG s_NextSecond = 0;
        static int s_FPS = 0;
        ++s_FPS;

        ULONGLONG uTickCount = GetTickCount64();
        if (uTickCount >= s_NextSecond)
        {
            s_NextSecond = (uTickCount + 1000);

            gGlobals.m_FixAnim_nTicksPerFrame = (4800 / s_FPS);

            s_FPS = 0;
        }
    }

    void __cdecl Computer_DeleteHandler()
    {
        reinterpret_cast<void(__cdecl*)()>(0x531B50)();
        Utils::QCamera_InitCurrent();
    }

    void __cdecl CutScene_RemoveHandler(void* p_CutScene)
    {
        reinterpret_cast<void(__cdecl*)(void*)>(0x43E540)(p_CutScene);
        Utils::QCamera_InitCurrent();
    }

    void __cdecl Human_GetHumanCameraInfoHandler(void* p_Human, void* p_CameraInfo)
    {
        if (Utils::Game_IsPaused())
        {
            __asm
            {
                // Reset world speed on human to prevent camera shake while paused.
                // The world speed will be set to original value by game after unpausing.

                xor eax, eax

                mov esi, p_Human
                add esi, 0x620

                mov [esi], eax
                mov [esi + 0x4], eax
                mov [esi + 0x8], eax
            }

            Helper::HumanPlayer_ResetAngleInput();
        } 
        
        reinterpret_cast<void(__cdecl*)(void*, void*)>(0x50F320)(p_Human, p_CameraInfo);
    }
}

namespace Core
{
    using namespace Patcher;

    void InitializePatches()
    {
        // Fix mouse cursor while in windowed mode
        ApplyByte(0x53164C, 0xEB);
        NopBytes(0x531816, 13);

        // Fix mouse input
        NopBytes(0x401D4A, 5); // Already called in InputPort_RunHandler, causes racial conditions.
        ApplyBytes(0x43851A, { 0xEB, 0x66 }); // Don't clamp analog X,Y values.

        // HumanView Animations
        NopBytes(0x4E5027, 2); // Remove if check to force animation update each frame.
        ApplyType<int*>(0x4B816C, &gGlobals.m_FixAnim_nTicksPerFrame);

        // Change windowed style to borderless window.
        ApplyType<uint32_t>(0x404692, (0x96080000 - WS_POPUP));
        ApplyType<uint32_t>(0x40469E, WS_POPUP);
        ApplyType<uint32_t>(0x4046AE, WS_POPUP);

    }

    void InitializeHooks()
    {
        using namespace Hooks;

        MakeCallRel32(0x44B73C, AppContext_SetInactive);

        ApplyType<void*>(0x44B9E3, Direct3D_SwapBuffers);
        ApplyType<void*>(0x531BEA, Computer_DeleteHandler);
        ApplyType<void*>(0x43E767, CutScene_RemoveHandler);
        ApplyType<void*>(0x514A30, Human_GetHumanCameraInfoHandler);
    }

    void InitializeSettings()
    {
        if (Settings::GetInteger("Windowed")) {
            NopBytes(0x404434, 6);
        }

        if (Settings::GetInteger("SkipIntroScreens")) {
            ApplyByte(0x447E4F, 0);
        }
    }
}

int __stdcall DllMain(HMODULE p_Module, DWORD p_Reason, void* p_Reserved)
{
    if (p_Reason == DLL_PROCESS_ATTACH)
    {
        CRT::Initialize(); // CRT
        DisableThreadLibraryCalls(p_Module);

        if (*reinterpret_cast<uint32_t*>(0x400140) != 0x3F7752D7)
        {
            MessageBoxA(0, "You're using wrong game version. GOG v1.3 is required for compatibility.", "IGI2 Patch", MB_OK | MB_ICONERROR);
            return 0;
        }

        Core::InitializePatches();
        Core::InitializeHooks();
        Core::InitializeSettings();
    }

    return 1;
}
