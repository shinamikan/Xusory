#pragma once

#include <array>
#include <vector>

#include "../Common/PlatformDefine.h"

namespace XusoryEngine
{
	enum class CpuArchitecture
	{
		X64 = PROCESSOR_ARCHITECTURE_AMD64,
		X86 = PROCESSOR_ARCHITECTURE_INTEL,
		ARM = PROCESSOR_ARCHITECTURE_ARM,
		ARM64 = PROCESSOR_ARCHITECTURE_ARM64,
		IA64 = PROCESSOR_ARCHITECTURE_IA64,
		UNKNOWN = PROCESSOR_ARCHITECTURE_UNKNOWN
	};

	DLL_STATIC_CLASS(CpuInfo)
	{
	public:
		static std::string GetCompleteCpuName();
		static std::string GetCpuVendor();
		static CpuArchitecture GetCpuArchitecture();
		static UINT GetNumberOfCpuCores();

	private:
		INTERNAL_CLASS(CpuInfo)
		{
		public:
			CpuInfo_Internal();

			UINT m_funcId;
			UINT m_exFuncId;
			std::string m_cpuVendor;
			std::string m_cpuName;
			std::vector<std::array<int, 4>> m_data;
			std::vector<std::array<int, 4>> m_exData;
		};
	};

	enum class BatteryState : BYTE
	{
		USING_POWER = 0,
		CHARGING = 1,
		UNKNOWN = 255
	};

	DLL_STATIC_CLASS(SystemInfo)
	{
	public:
		static std::wstring GetNativeName();
		static std::wstring GetComputerUserName();

		static std::wstring GetSystemLanguage();
		static UINT16 GetSystemLanguageId();

		static UINT8 GetBatteryPercentage();
		static BatteryState GetBatteryState();
		static BOOL GetSavingPowerModeState();

		static std::wstring GetEnvironmentVar(const std::wstring_view& key);
		static void SetEnvironmentVar(const std::wstring_view& key, const std::wstring_view& value);
	};

	DLL_STATIC_CLASS(ScreenInfo)
	{
		static Point GetMainScreenSize();
		static INT GetScreenNum();
	};
}
