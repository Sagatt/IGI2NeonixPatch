#pragma once

//===========================================================
// malloc, free, realloc

void* __cdecl malloc(size_t _Size)
{
    return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, _Size);
}

void __cdecl free(void* _Block)
{
    HeapFree(GetProcessHeap(), 0, _Block);
}

void* __cdecl realloc(void* _Block, size_t _Size)
{
    if (!_Size)
    {
        free(_Block);
        return nullptr;
    }

    if (!_Block) {
        return malloc(_Size);
    }

    return HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, _Block, _Size);
}

//===========================================================
// Operators: new, new[], delete, delete[]

void* operator new(size_t _Size)
{
    return malloc(_Size);
}

void* operator new[](size_t _Size)
{
    return malloc(_Size);
}

void operator delete(void* _Block) noexcept
{
    free(_Block);
}

void operator delete(void* _Block, size_t _Size) noexcept
{
    free(_Block);
}

void operator delete[](void* _Block) noexcept
{
    free(_Block);
}

void operator delete[](void* _Block, size_t _Size) noexcept
{
    free(_Block);
}