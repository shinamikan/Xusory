#include "../Time.h"

namespace XusoryEngine
{
	FileTime AdjustFileTimeToLocal(const FileTime& utcFileTime)
	{
		FileTime localFileTime;
		ThrowIfWinFuncFailed(FileTimeToLocalFileTime(&utcFileTime, &localFileTime), "adjust time");

		return localFileTime;
	}

	FileTime AdjustFileTimeToUTC(const FileTime& localFileTime)
	{
		FileTime utcFileTime;
		ThrowIfWinFuncFailed(LocalFileTimeToFileTime(&localFileTime, &utcFileTime), "adjust time");

		return utcFileTime;
	}

	FileTime Time::CompTimeToFileTime(const CompleteTime& compTime, BOOL currentToLocal)
	{
		FileTime fileTime;
		ThrowIfWinFuncFailed(SystemTimeToFileTime(&compTime, &fileTime), "converse time");

		if (currentToLocal)
		{
			fileTime = AdjustFileTimeToUTC(fileTime);
		}
		return fileTime;
	}

	CompleteTime Time::FileTimeToCompTime(const FileTime& fileTime, BOOL currentToLocal)
	{
		FileTime fileTimeTemp = fileTime;
		if (currentToLocal)
		{
			fileTimeTemp = AdjustFileTimeToLocal(fileTime);
		}

		CompleteTime compTime;
		ThrowIfWinFuncFailed(FileTimeToSystemTime(&fileTimeTemp, &compTime), "converse time");

		return compTime;
	}

	DOUBLE Time::FileTimeToTimeStamp(const FileTime& fileTime, BOOL currentToLocal)
	{
		FileTime fileTimeTemp = fileTime;
		if (currentToLocal)
		{
			fileTimeTemp = AdjustFileTimeToLocal(fileTime);
		}

		ULARGE_INTEGER uli;
		uli.LowPart = fileTimeTemp.dwLowDateTime;
		uli.HighPart = fileTimeTemp.dwHighDateTime;

		return static_cast<DOUBLE>(uli.QuadPart - TIME_DIFFERENCE_1601_TO_1970) / FILE_TIME_TO_TIME_STAMP;
	}

	std::wstring Time::FormatTime(const CompleteTime& compTime, const std::wstring_view& formatInfo)
	{
		const INT bufSize = GetTimeFormatEx(LOCALE_NAME_SYSTEM_DEFAULT, NULL, nullptr, formatInfo.data(), nullptr, 0);
		std::wstring buf(bufSize - 1, 0);

		const BOOL result = GetTimeFormatEx(LOCALE_NAME_SYSTEM_DEFAULT, NULL, &compTime, formatInfo.data(), buf.data(), static_cast<int>(buf.size() + 1));
		ThrowIfWinFuncFailed(result, "format time");

		return buf;
	}

	CompleteTime Time::GetUTCCompTime()
	{
		CompleteTime time;
		GetSystemTime(&time);

		return time;
	}

	std::wstring Time::GetUTCFormatTime(const std::wstring_view& formatInfo)
	{
		const CompleteTime compTime = GetUTCCompTime();
		return FormatTime(compTime, formatInfo);
	}
	
	CompleteTime Time::GetLocalCompTime()
	{
		CompleteTime time;
		GetLocalTime(&time);

		return time;
	}

	DOUBLE Time::GetLocalTimeStamp()
	{
		FileTime fileTime;
		GetSystemTimePreciseAsFileTime(&fileTime);

		const DOUBLE timeSince1970 = FileTimeToTimeStamp(fileTime, false);
		return timeSince1970;
	}

	std::wstring Time::GetLocalFormatTime(const std::wstring_view& formatInfo)
	{
		const CompleteTime compTime = GetLocalCompTime();
		return FormatTime(compTime, formatInfo);
	}

	PerformanceTime::PerformanceTime_Internal PerformanceTime::sm_internalPerformanceTime;
	DOUBLE PerformanceTime::GetTime()
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);

		return static_cast<DOUBLE>(currentTime.QuadPart) * sm_internalPerformanceTime.m_timeCycle;
	}

	PerformanceTime::PerformanceTime_Internal::PerformanceTime_Internal()
	{
		INT64 timeFrequency = 0;
		QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&timeFrequency));
		m_timeCycle = 1.0 / static_cast<DOUBLE>(timeFrequency);
	}
}
