#pragma once
#include <xutility>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-noreturn"

_STD_BEGIN

[[noreturn]] void _Xbad_alloc() { }
[[noreturn]] void _Xinvalid_argument(const char*) { }
[[noreturn]] void _Xlength_error(const char*) { }
[[noreturn]] void _Xout_of_range(const char*) { }
[[noreturn]] void _Xoverflow_error(const char*) { }
[[noreturn]] void _Xruntime_error(const char*) { }
[[noreturn]] void _XGetLastError() { }

_STD_END

#pragma clang diagnostic pop