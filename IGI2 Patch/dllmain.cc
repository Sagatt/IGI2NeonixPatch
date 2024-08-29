//==========================================================================
// Includes

#include "Includes.hh"
#include "3rdParty/CRT-STL/CRT-STL.hh"

namespace Utils
{
    void __fastcall QCamera_InitCurrent()
    {
        __asm
        {
            mov eax, dword ptr [0x83685EC]
            add eax, 0x80

            mov ecx, 0x575E60
            call ecx
        }
    }

}

namespace Hooks
{
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

    void __cdecl CutScene_RemoveHandler(void* p_CutScene)
    {
        reinterpret_cast<void(__cdecl*)(void*)>(0x43E540)(p_CutScene);
        Utils::QCamera_InitCurrent();
    }
}

namespace Core
{
    using namespace Patcher;

    void InitializePatches()
    {
        // Fix mouse input
        NopBytes(0x401D4A, 5); // Already called in InputPort_RunHandler, causes racial conditions.
        ApplyBytes(0x43851A, { 0xEB, 0x66 }); // Don't clamp analog X,Y values.

        // HumanView Animations
        NopBytes(0x4E5027, 2); // Remove if check to force animation update each frame.
        ApplyType<int*>(0x4B816C, &gGlobals.m_FixAnim_nTicksPerFrame);

    }

    void InitializeHooks()
    {
        using namespace Hooks;

        ApplyType<void*>(0x44B9E3, Direct3D_SwapBuffers);
        ApplyType<void*>(0x43E767, CutScene_RemoveHandler);
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
    }

    return 1;
}
