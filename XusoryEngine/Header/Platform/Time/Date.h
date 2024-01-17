#pragma once

#include "../Common/PlatformDefine.h"

namespace XusoryEngine
{
	using CompleteTime = SYSTEMTIME;

	enum Month
	{
		MONTH_JAN = 1, MONTH_FEB, MONTH_MAR, MONTH_APR,
		MONTH_MAY, MONTH_JUN, MONTH_JUL, MONTH_AUG,
		MONTH_SEP, MONTH_OCT, MONTH_NOV, MONTH_DEC
	};

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
