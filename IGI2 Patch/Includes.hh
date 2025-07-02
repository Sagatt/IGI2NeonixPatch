#pragma once

//==========================================================================
// Libraries

#define _CRT_SECURE_NO_WARNINGS
#include <cstdint>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d9.h>
#include <sysinfoapi.h>

//==========================================================================
// Preprocessors

#define IGI_INLINE __forceinline

//==========================================================================
// Core (Includes)

// Utils

#include "Core/Utils/Patcher.hh"
#include "Core/Utils/Utils.hh"
#include "Core/Utils/Settings.hh"


#include "Core/Globals.hh"
#include "Core/AIVoiceTable.hh"