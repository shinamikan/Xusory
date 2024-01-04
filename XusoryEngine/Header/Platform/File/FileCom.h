#pragma once

#include "../Common/PlatformCom.h"

namespace NovaEngine::Platform
{
	enum OPEN_MODE
	{
		OPEN_MODE_NULL		= NULL,
		OPEN_MODE_READ		= static_cast<int>(GENERIC_READ),
		OPEN_MODE_WRITE		= static_cast<int>(GENERIC_WRITE),
		OPEN_MODE_APPEND	= FILE_APPEND_DATA,
		OPEN_MODE_READ_ADD	= OPEN_MODE_READ + 1,
		OPEN_MODE_WRITE_ADD	= OPEN_MODE_WRITE + 1,
		OPEN_MODE_APPEND_ADD = OPEN_MODE_APPEND + 1
	};

	enum FILE_TIME_INFO
	{
		FILE_CREATION_TIME = 0,
		FILE_LAST_ACCESS_TIME,
		FILE_LAST_WRITE_TIME
	};

	constexpr char NO_SUCH_PATH_ERROR_INFO[] = "No such File or Directory";
	constexpr char PATH_EXIST_ERROR_INFO[] = "File or Directory already exist";

	STD_ERROR_CLASS(DirectoryOperationError, RuntimeError)
	END_CLASS;

	STD_ERROR_CLASS(FileNotOpenedError, LogicError)
	END_CLASS;

	STD_ERROR_CLASS(FileOperationError, RuntimeError)
	END_CLASS;

	STD_ERROR_CLASS(OpenModeError, LogicError)
	END_CLASS;

	STD_ERROR_CLASS(PathError, RuntimeError)
	END_CLASS;

	STD_ERROR_CLASS(PathExistError, RuntimeError)
	END_CLASS;

	STD_ERROR_CLASS(PathNotFoundError, RuntimeError)
	END_CLASS;

	inline std::string GetPathErrorCompInfo(const std::string_view& info, const std::wstring_view& path)
	{
		return std::string(info) + ", Path: " + StringEx::WStringToString(path);
	}
}
