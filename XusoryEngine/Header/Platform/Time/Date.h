#pragma once

#include "TimeCom.h"

namespace XusoryEngine::Platform
{
	DLL_STATIC_CLASS(Date)
	{
	public:
		static std::wstring FormatDate(const CompleteTime& compDate, const std::wstring_view& formatInfo);
		static std::wstring GetLocalFormatDate(const std::wstring_view& formatInfo = TEXT("yyyy-MM-dd"));

		static void AddYear(CompleteTime& compDate, UINT year = 1);
		static void AddMonth(CompleteTime& compDate, UINT month = 1);
		static void AddDay(CompleteTime& compDate, UINT day = 1);
		static void CorrectDate(CompleteTime& compDate);

		static BOOL CompareDate(const CompleteTime& lDate, const CompleteTime& rDate);
		static BOOL IsBefore(CompleteTime& lDate, CompleteTime& rDate);
		static BOOL IsLeapYear(const CompleteTime& compDate);
		static BOOL IsValidDate(const CompleteTime& compDate);
	};
}
