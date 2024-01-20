#pragma once

#include <iostream>
#include <Windows.h>

#include "../../CppEx/CppEx.h"
#include "../../StdEx/StdEx.h"

namespace XusoryEngine
{
	using Point = POINT;
	using Rect = RECT;

	inline std::string HasCreatedInfo(const std::string_view& objectInfo)
	{
		return StringEx::Format<std::string>("The %s has been created or opened", objectInfo.data());
	}

	inline std::string HasNotCreatedInfo(const std::string_view& objectInfo)
	{
		return StringEx::Format<std::string>("The %s has not been created or opened yet", objectInfo.data());
	}

	inline std::string FailedInfo(const std::string_view& operatorInfo)
	{
		return StringEx::Format<std::string>("Failed to %s", operatorInfo.data());
	}

	inline std::string FailedInfoWithErrorCode(const std::string_view& operatorInfo, INT errorCode)
	{
		return StringEx::Format<std::string>("Failed to %s, error code: %d", operatorInfo.data(), errorCode);
	}

	inline std::string WinFailedInfo(const std::string_view& operatorInfo)
	{
		return StringEx::Format<std::string>("Failed to %s, error code: %d", operatorInfo.data(), GetLastError());
	}

	inline void ThrowIfObjectNotCreated(const void* handle, const std::string_view& objectInfo)
	{
		if (!handle)
		{
			ThrowWithErrName(LogicError, HasNotCreatedInfo(objectInfo));
		}
	}

	inline void ThrowIfObjectHasCreated(const void* handle, const std::string_view& objectInfo)
	{
		if (handle)
		{
			ThrowWithErrName(LogicError, HasCreatedInfo(objectInfo));
		}
	}

	inline void ThrowIfWinFuncFailed(BOOL result, const std::string_view& operatorInfo)
	{
		if (!result)
		{
			ThrowWithErrName(RuntimeError, WinFailedInfo(operatorInfo));
		}
	}
}
