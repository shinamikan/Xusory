#pragma once

#include "../Common/PlatformDefine.h"

#pragma warning(disable : 4251)

namespace XusoryEngine
{
	using FileTime = FILETIME;
	using CompleteTime = SYSTEMTIME;

	constexpr UINT64 TIME_DIFFERENCE_1601_TO_1970 = 116444736000000000ULL;
	constexpr DOUBLE FILE_TIME_TO_TIME_STAMP = 10000000.0;

	DLL_STATIC_CLASS(Time)
	{
	public:
		static FileTime		CompTimeToFileTime(const CompleteTime& compTime, BOOL currentToLocal);
		static CompleteTime FileTimeToCompTime(const FileTime& fileTime, BOOL currentToLocal);
		static DOUBLE		FileTimeToTimeStamp(const FileTime& fileTime, BOOL currentToLocal);
		
		static std::wstring FormatTime(const CompleteTime& compTime, const std::wstring_view& formatInfo);

		static CompleteTime GetUTCCompTime();
		static std::wstring GetUTCFormatTime(const std::wstring_view& formatInfo = TEXT("HH:mm:ss"));

		static CompleteTime GetLocalCompTime();
		static DOUBLE		GetLocalTimeStamp();
		static std::wstring GetLocalFormatTime(const std::wstring_view& formatInfo = TEXT("HH:mm:ss"));
	};

	DLL_STATIC_CLASS(PerformanceTime)
	{
	public:
		static DOUBLE GetTime();

	private:
		INTERNAL_CLASS(PerformanceTime)
		{
		public:
			PerformanceTime_Internal();

			DOUBLE m_timeCycle;
		};
	};
}
