#pragma once

#include <iostream>
#include <Windows.h>

#include "../../CppEx/CppEx.h"
#include "../../StdEx/StdEx.h"

namespace XusoryEngine::Platform
{
	inline std::string FailedInfo(const std::string_view& info)
	{
		return StringEx::Format<std::string>("Failed to %s", info.data());
	}

	inline std::string FailedInfoWithErrorCode(const std::string_view& info, INT errorCode)
	{
		return StringEx::Format<std::string>("Failed to %s, error code: %d", info.data(), errorCode);
	}

	inline std::string WinFailedInfo(const std::string_view& info)
	{
		return StringEx::Format<std::string>("Failed to %s, error code: %d", info.data(), GetLastError());
	}
}

