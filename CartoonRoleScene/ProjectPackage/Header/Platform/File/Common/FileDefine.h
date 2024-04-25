#pragma once

#include "../../Common/PlatformDefine.h"

namespace XusoryEngine
{
	constexpr char NO_SUCH_PATH_ERROR_INFO[] = "No such file or directory";
	constexpr char PATH_EXIST_ERROR_INFO[] = "The file or directory already exist";

	inline std::string GetPathErrorCompInfo(const std::string_view& info, const std::wstring_view& path)
	{
		return std::string(info) + ", Path: " + StringEx::WStringToString(path);
	}

	STD_ERROR_CLASS(PathError, LogicError)
	END_CLASS;

	STD_ERROR_CLASS(PathExistError, RuntimeError)
	END_CLASS;

	STD_ERROR_CLASS(PathNotFoundError, RuntimeError)
	END_CLASS;
}
