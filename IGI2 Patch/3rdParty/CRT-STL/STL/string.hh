#pragma once
#include <cstring>
#include <string.h>

//===================================================================
// mem (Functions)

STL_INLINE void* memcpy(void* _Dst, void const* _Src, size_t _Size)
{
	asm volatile(
		"rep movsb"
		: "+D"(_Dst), "+S"(_Src), "+c"(_Size)
		:
		: "memory"
	);
	return _Dst;
}

STL_INLINE void* memmove(void* _Dst, void const* _Src, size_t _Size)
{
	return memcpy(_Dst, _Src, _Size);
}

void* memset(void* _Dst, int _Val, size_t _Size)
{
	asm volatile(
		"rep stosb"
		: "+D"(_Dst), "+c"(_Size)
		: "a"(_Val)
		: "memory"
	);
	return _Dst;
}

//===================================================================
// str (Functions)

size_t strlen(const char* str)
{
	const char* s;

	for (s = str; *s; ++s);

	return(s - str);
}

char* strcat(char* s, const char* append)
{
	char* pSave = s;

	for (; *s; ++s);

	while (*append) {
		*s++ = *append++;
	}

	return pSave;
}

const char* strrchr(const char* _String, int _Ch)
{
	const char* pSave;
	char c;

	for (; (c = *_String); ++_String)
	{
		if (c == _Ch) {
			pSave = _String;
		}
	}

	return pSave;
}