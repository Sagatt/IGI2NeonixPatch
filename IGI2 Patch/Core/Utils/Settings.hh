#pragma once

#define CORE_SETTINGS_FILE_NAME	".\\settings.ini"

namespace Settings
{
	inline char stringBuffer[128];

	IGI_INLINE bool SetString(const char* p_Section, const char* p_Key, const char* p_String)
	{
		return (WritePrivateProfileStringA(p_Section, p_Key, p_String, CORE_SETTINGS_FILE_NAME) != 0);
	}

	IGI_INLINE bool SetString(const char* p_Key, const char* p_String)
	{
		return SetString("IGI2", p_Key, p_String);
	}

	IGI_INLINE const char* GetString(const char* p_Section, const char* p_Key, const char* p_Default = nullptr)
	{
		GetPrivateProfileStringA(p_Section, p_Key, p_Default, stringBuffer, sizeof(stringBuffer), CORE_SETTINGS_FILE_NAME);
		return stringBuffer;
	}

	IGI_INLINE const char* GetString(const char* p_Key, const char* p_Default = nullptr)
	{
		return GetString("IGI2", p_Key, p_Default);
	}

	IGI_INLINE int GetInteger(const char* p_Section, const char* p_Key, int p_Default = 0)
	{
		return static_cast<int>(GetPrivateProfileIntA(p_Section, p_Key, p_Default, CORE_SETTINGS_FILE_NAME));
	}

	IGI_INLINE int GetInteger(const char* p_Key, int p_Default = 0)
	{
		return GetInteger("IGI2", p_Key, p_Default);
	}
};