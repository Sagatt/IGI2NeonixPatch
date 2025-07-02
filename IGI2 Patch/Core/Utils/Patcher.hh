#pragma once
#include <initializer_list>
#include <intrin.h>
#include <cstdint>

namespace Patcher
{
    //==============================================================

    bool ApplyData(void* p_Address, void* p_Data, size_t p_Size);

    template <typename T>
    __forceinline bool ApplyType(uintptr_t p_Address, T p_Value)
    {
        return ApplyData(reinterpret_cast<void*>(p_Address), &p_Value, sizeof(T));
    }

    //==============================================================

    __forceinline bool ApplyBytes(uintptr_t p_Address, std::initializer_list<uint8_t> p_Bytes)
    {
        size_t sSize = p_Bytes.size();
        return ApplyData(reinterpret_cast<void*>(p_Address), (void*)(p_Bytes.begin()), sSize);
    }

    template <size_t N>
    __forceinline bool ApplyBytes(uintptr_t p_Address, const uint8_t(&p_Bytes)[N])
    {
        return ApplyData(reinterpret_cast<void*>(p_Address), (void*)p_Bytes, N);
    }

    __forceinline bool ApplyByte(uintptr_t p_Address, uint8_t p_Byte)
    {
        return ApplyBytes(p_Address, { p_Byte });
    }

    //==============================================================

    bool NopBytes(uintptr_t p_Address, size_t p_NumBytes);

    bool Int3Bytes(uintptr_t p_Address, size_t p_NumBytes);

    //==============================================================
    // p_Address -> E8 (Call) / E9 (Jump)

    bool JmpRel32(uintptr_t p_Address, void* p_Target);

    bool JmpRel32(uint8_t p_Opcode, uintptr_t p_Address, void* p_Target);

    __forceinline bool MakeCallRel32(uintptr_t p_Address, void* p_Target)
    {
        return JmpRel32(0xE8, p_Address, p_Target);
    }

    __forceinline  bool MakeJmpRel32(uintptr_t p_Address, void* p_Target)
    {
        return JmpRel32(0xE9, p_Address, p_Target);
    }
};