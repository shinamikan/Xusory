#pragma once

#include "TimeCom.h"

namespace NovaEngine::Platform
{
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
		static void Init();
		static DOUBLE GetTime();

	private:
		static DOUBLE sm_timeCycle;
	};
}
