#include <intrin.h>
#include "../SystemInfo.h"

namespace XusoryEngine
{
	CpuInfo::CpuInfo_Internal CpuInfo::sm_internalCpuInfo;
	std::string CpuInfo::GetCompleteCpuName()
	{
		return sm_internalCpuInfo.m_cpuName;
	}

	std::string CpuInfo::GetCpuVendor()
	{
		return sm_internalCpuInfo.m_cpuVendor;
	}

	CpuArchitecture CpuInfo::GetCpuArchitecture()
	{
		SYSTEM_INFO info;
		GetSystemInfo(&info);

		return static_cast<CpuArchitecture>(info.wProcessorArchitecture);
	}

	UINT CpuInfo::GetNumberOfCpuCores()
	{
		SYSTEM_INFO info;
		GetSystemInfo(&info);

		return info.dwNumberOfProcessors;
	}

	CpuInfo::CpuInfo_Internal::CpuInfo_Internal()
	{
		std::array<int, 4> cpuId;

		__cpuid(cpuId.data(), 0);
		m_funcId = cpuId[0];

		for (UINT i = 0; i <= m_funcId; ++i)
		{
			__cpuidex(cpuId.data(), static_cast<INT>(i), 0);
			m_data.push_back(cpuId);
		}

		m_cpuVendor.resize(0x20, 0);
		*reinterpret_cast<int*>(m_cpuVendor.data()) = m_data[0][1];
		*reinterpret_cast<int*>(m_cpuVendor.data() + 4) = m_data[0][3];
		*reinterpret_cast<int*>(m_cpuVendor.data() + 8) = m_data[0][2];

		__cpuid(cpuId.data(), static_cast<INT>(0x80000000));
		m_exFuncId = cpuId[0];

		m_cpuName.resize(0x40, 0);

		for (UINT i = 0x80000000; i <= m_exFuncId; ++i)
		{
			__cpuidex(cpuId.data(), static_cast<INT>(i), 0);
			m_exData.push_back(cpuId);
		}

		if (m_exFuncId >= 0x80000004)
		{
			memcpy(m_cpuName.data(), m_exData[2].data(), sizeof(cpuId));
			memcpy(m_cpuName.data() + 16, m_exData[3].data(), sizeof(cpuId));
			memcpy(m_cpuName.data() + 32, m_exData[4].data(), sizeof(cpuId));
		}
	}

	std::wstring SystemInfo::GetNativeName()
	{
		DWORD bufSize = MAX_COMPUTERNAME_LENGTH + 1;
		std::wstring name(bufSize, 0);
		GetComputerName(name.data(), &bufSize);

		return name;
	}

	std::wstring SystemInfo::GetComputerUserName()
	{
		DWORD bufSize = MAX_COMPUTERNAME_LENGTH + 1;
		std::wstring name(bufSize, 0);
		GetUserName(name.data(), &bufSize);

		return name;
	}

	std::wstring SystemInfo::GetSystemLanguage()
	{
		ULONG languageNum;
		ULONG bufSize = MAX_COMPUTERNAME_LENGTH + 1;

		std::wstring languageName(bufSize, 0);
		GetSystemPreferredUILanguages(MUI_LANGUAGE_NAME, &languageNum, languageName.data(), &bufSize);

		return languageName;
	}

	UINT16 SystemInfo::GetSystemLanguageId()
	{
		return GetUserDefaultUILanguage();
	}

	UINT8 SystemInfo::GetBatteryPercentage()
	{
		SYSTEM_POWER_STATUS powerStatus;
		GetSystemPowerStatus(&powerStatus);

		return powerStatus.BatteryLifePercent;
	}

	BatteryState SystemInfo::GetBatteryState()
	{
		SYSTEM_POWER_STATUS powerStatus;
		GetSystemPowerStatus(&powerStatus);

		return static_cast<BatteryState>(powerStatus.ACLineStatus);
	}

	BOOL SystemInfo::GetSavingPowerModeState()
	{
		SYSTEM_POWER_STATUS powerStatus;
		GetSystemPowerStatus(&powerStatus);

		return powerStatus.SystemStatusFlag;
	}

	std::wstring SystemInfo::GetEnvironmentVar(const std::wstring_view& key)
	{
		std::wstring buf(MAX_PATH, 0);
		if (GetEnvironmentVariable(key.data(), buf.data(), MAX_PATH) == 0)
		{
			ThrowWithErrName(RuntimeError, "There is no environment variable for this key");
		}

		return buf;
	}

	void SystemInfo::SetEnvironmentVar(const std::wstring_view& key, const std::wstring_view& value)
	{
		ThrowIfWinFuncFailed(SetEnvironmentVariable(key.data(), value.data()), "set environment variable") ;
	}

	Point ScreenInfo::GetMainScreenSize()
	{
		return { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
	}

	INT ScreenInfo::GetScreenNum()
	{
		return GetSystemMetrics(SM_CMONITORS);
	}
}
