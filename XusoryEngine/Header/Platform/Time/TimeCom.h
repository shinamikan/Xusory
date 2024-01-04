#pragma once

#include "../Common/PlatformCom.h"

namespace NovaEngine
{
namespace Platform
{
	using FileTime = FILETIME;
	using CompleteTime = SYSTEMTIME;

	constexpr UINT64 TIME_DIFFERENCE_1601_TO_1970 = 116444736000000000ULL;
	constexpr DOUBLE FILE_TIME_TO_TIME_STAMP = 10000000.0;

	enum Month
	{
		Jan = 1,
		Feb,
		Mar,
		Apr,
		May,
		Jun,
		Jul,
		Aug,
		Sep,
		Oct,
		Nov,
		Dec
	};
}
}

