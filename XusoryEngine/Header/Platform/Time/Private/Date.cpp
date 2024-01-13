#include "../Date.h"
#include "../Time.h"

#include <unordered_map>

namespace XusoryEngine
{
	std::wstring Date::FormatDate(const CompleteTime& compDate, const std::wstring_view& formatInfo)
	{
		const INT bufSize = GetDateFormatEx(LOCALE_NAME_SYSTEM_DEFAULT, NULL, nullptr, formatInfo.data(), nullptr, 0, nullptr);

		std::wstring buf(bufSize - 1, 0);
		const BOOL result = GetDateFormatEx(LOCALE_NAME_SYSTEM_DEFAULT, NULL, &compDate, formatInfo.data(), buf.data(), static_cast<int>(buf.size() + 1), nullptr);
		ThrowIfWinFuncFailed(result, "format date");

		return buf;
	}

	std::wstring Date::GetLocalFormatDate(const std::wstring_view& formatInfo)
	{
		const CompleteTime compTime = Time::GetLocalCompTime();
		return FormatDate(compTime, formatInfo);
	}

	void Date::AddYear(CompleteTime& compDate, UINT year)
	{
		compDate.wYear += year;
	}

	void Date::AddMonth(CompleteTime& compDate, UINT month)
	{
		compDate.wMonth += month;

		while (compDate.wMonth > 12)
		{
			compDate.wMonth -= 12;
			AddYear(compDate);
		}
	}

	void Date::AddDay(CompleteTime& compDate, UINT day)
	{
		compDate.wDay += day;

		while (true)
		{
			if (IsValidDate(compDate))
			{
				break;
			}

			switch (compDate.wMonth)
			{
			case Jan:
			case Mar:
			case May:
			case Jul:
			case Aug:
			case Oct:
			case Dec:
				compDate.wDay -= 31;
				AddMonth(compDate);
				break;
			case Apr:
			case Jun:
			case Sep:
			case Nov:
				compDate.wDay -= 30;
				AddMonth(compDate);
				break;
			default:
				UINT dayNum;
				if (IsLeapYear(compDate))
				{
					dayNum = 29;
				}
				else
				{
					dayNum = 28;
				}
				compDate.wDay -= dayNum;
				AddMonth(compDate);
			}
		}
	}

	void Date::CorrectDate(CompleteTime& compDate)
	{
		AddDay(compDate, 0);
	}

	BOOL Date::CompareDate(const CompleteTime& lDate, const CompleteTime& rDate)
	{
		return lDate.wYear == rDate.wYear && lDate.wMonth == rDate.wMonth && lDate.wDay == rDate.wDay;
	}

	BOOL Date::IsBefore(CompleteTime& lDate, CompleteTime& rDate)
	{
		if (!IsValidDate(lDate) || !IsValidDate(rDate))
		{
			CorrectDate(lDate);
			CorrectDate(rDate);
		}

		if (lDate.wYear == rDate.wYear)
		{
			if (lDate.wMonth == rDate.wMonth)
			{
				if (lDate.wDay == rDate.wDay)
				{
					return false;
				}
				return lDate.wDay < rDate.wDay;
			}
			return lDate.wMonth < rDate.wMonth;
		}
		return lDate.wYear < rDate.wYear;
	}

	BOOL Date::IsLeapYear(const CompleteTime& compDate)
	{
		if (compDate.wYear % 400 == 0)
		{
			return true;
		}

		if (compDate.wYear % 4 == 0)
		{
			if (compDate.wYear % 100 == 0)
			{
				return false;
			}
			return true;
		}
		return false;
	}

	BOOL Date::IsValidDate(const CompleteTime& compDate)
	{
		if (compDate.wMonth > 12)
		{
			return false;
		}

		switch (compDate.wMonth)
		{
		case Jan:
		case Mar:
		case May:
		case Jul:
		case Aug:
		case Oct:
		case Dec:
			if (compDate.wDay <= 31)
			{
				return true;
			}
		case Apr:
		case Jun:
		case Sep:
		case Nov:
			if (compDate.wDay <= 30)
			{
				return true;
			}
		default:
			UINT dayNum;
			if (IsLeapYear(compDate))
			{
				dayNum = 29;
			}
			else
			{
				dayNum = 28;
			}
			if (compDate.wDay <= dayNum)
			{
				return true;
			}
		}
		return false;
	}
}
