#include <Windows.h>
#include "Patcher.hh"

#define MEM_PROTECT(address, size, protect, oldprotect) VirtualProtect(address, size, protect, oldprotect)

namespace Patcher
{
    bool ApplyData(void* p_Address, void* p_Data, size_t p_Size)
    {
        DWORD dwOldProtection;
        if (!MEM_PROTECT(p_Address, p_Size, PAGE_EXECUTE_READWRITE, &dwOldProtection)) {
            return false;
        }

        __movsb(reinterpret_cast<uint8_t*>(p_Address), reinterpret_cast<uint8_t*>(p_Data), p_Size);

        MEM_PROTECT(p_Address, p_Size, dwOldProtection, &dwOldProtection);
        return true;
    }

    bool NopBytes(uintptr_t p_Address, size_t p_NumBytes)
    {
        DWORD dwOldProtection;
        if (!MEM_PROTECT(reinterpret_cast<void*>(p_Address), p_NumBytes, PAGE_EXECUTE_READWRITE, &dwOldProtection)) {
            return false;
        }

        __stosb(reinterpret_cast<uint8_t*>(p_Address), 0x90, p_NumBytes);

        MEM_PROTECT(reinterpret_cast<void*>(p_Address), p_NumBytes, dwOldProtection, &dwOldProtection);
        return true;
    }

    bool Int3Bytes(uintptr_t p_Address, size_t p_NumBytes)
    {
        DWORD dwOldProtection;
        if (!MEM_PROTECT(reinterpret_cast<void*>(p_Address), p_NumBytes, PAGE_EXECUTE_READWRITE, &dwOldProtection)) {
            return false;
        }

        __stosb(reinterpret_cast<uint8_t*>(p_Address), 0xCC, p_NumBytes);

        MEM_PROTECT(reinterpret_cast<void*>(p_Address), p_NumBytes, dwOldProtection, &dwOldProtection);
        return true;
    }

    bool JmpRel32(uintptr_t p_Address, void* p_Target)
    {
        uint32_t uJmpOffset = (reinterpret_cast<uint32_t>(p_Target) - p_Address - 5);

        return ApplyData(reinterpret_cast<void*>(p_Address + 1), &uJmpOffset, sizeof(uJmpOffset));
    }

    bool JmpRel32(uint8_t p_Opcode, uintptr_t p_Address, void* p_Target)
    {
        uint8_t uBytes[5] = { p_Opcode };
        *reinterpret_cast<uint32_t*>(&uBytes[1]) = (reinterpret_cast<uint32_t>(p_Target) - p_Address - 5);

        return ApplyData(reinterpret_cast<void*>(p_Address), uBytes, sizeof(uBytes));
    }
};