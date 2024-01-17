#pragma once

#include "../Common/PlatformDefine.h"

namespace XusoryEngine
{
	DLL_STATIC_CLASS(CPUInfo)
	{

	};

	enum class BatteryState : BYTE
	{
		USING_POWER = 0,
		CHARGING = 1,
		UNKNOWN = 255
	};

	DLL_STATIC_CLASS(SystemInfo)
	{
		static std::wstring GetNativeName();
		static std::wstring GetComputerUserName();

		static std::wstring GetSystemLanguage();
		static UINT16 GetSystemLanguageId();

		static UINT8 GetBatteryPercentage();
		static BatteryState GetBatteryState();
		static BOOL GetSavingPowerModeState();

		static std::wstring GetEnvironmentVar(const std::wstring_view& key);
		static std::wstring SetEnvironmentVar(const std::wstring_view & key, const std::wstring_view & value);
	};

	DLL_STATIC_CLASS(ScreenInfo)
	{

	};
}
