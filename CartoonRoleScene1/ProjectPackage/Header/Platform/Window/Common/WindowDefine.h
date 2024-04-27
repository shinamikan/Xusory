#pragma once

#include "../../Common/PlatformDefine.h"

namespace XusoryEngine
{
	constexpr INT DEFAULT_WIN_POS = CW_USEDEFAULT;
	constexpr INT DEFAULT_WIN_SIZE = CW_USEDEFAULT;

	enum class SysCursor : INT
	{
		ARROW = 32512,
		TEXT_SELECT = 32513,
		WAIT = 32514,
		CROSS = 32515,
		UP_ARROW = 32516,
		HANDWRITING = 32631,
		SIZE_NW_SE = 32642,
		SIZE_NE_SW = 32643,
		SIZE_WE = 32644,
		SIZE_NS = 32645,
		SIZE_ALL = 32646,
		NO = 32648,
		HAND = 32649,
		APP_STARTING = 32650,
		APP_HELP = 32651,
		APP_PIN = 32671,
		APP_PERSON = 32672
	};

	enum class SysIcon : INT
	{
		APPLICATION = 32512,
		ERR = 32513,
		QUESTION = 32514,
		WARNING = 32515,
		INFORMATION = 32516,
		SHIELD = 32518
	};

	enum class MessageBoxStyle
	{
		OK = MB_OK,
		OK_CANCEL = MB_OKCANCEL,
		YES_NO = MB_YESNO,
		YES_NO_CANCEL = MB_YESNOCANCEL,
		RETRY_CANCEL = MB_RETRYCANCEL,
		ABORT_RETRY_IGNORE = MB_ABORTRETRYIGNORE,
		CANCEL_TRY_CONTINUE = MB_CANCELTRYCONTINUE,
	};

	enum class MessageBoxIcon
	{
		STOP = MB_ICONSTOP,
		WARNING = MB_ICONWARNING,
		QUESTION = MB_ICONQUESTION,
		INFORMATION = MB_ICONINFORMATION
	};

	enum class MessageBoxCode
	{
		CODE_NO = IDNO,
		CODE_OK = IDOK,
		CODE_YES = IDYES,
		CODE_ABORT = IDABORT,
		CODE_RETRY = IDRETRY,
		CODE_CANCEL = IDCANCEL,
		CODE_IGNORE = IDIGNORE,
		CODE_CONTINUE = IDCONTINUE,
		CODE_TRY_AGAIN = IDTRYAGAIN,
	};
}
