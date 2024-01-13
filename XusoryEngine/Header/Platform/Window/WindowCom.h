#pragma once

#include "../Common/PlatformCom.h"

namespace XusoryEngine
{
	using Point = POINT;
	using Rect	= RECT;

	using WinID = HWND;
	using WindowClass = WNDCLASS;
	using WindowClassEx = WNDCLASSEX;
	
	constexpr INT DEFAULT_WIN_POS = CW_USEDEFAULT;
	constexpr INT DEFAULT_WIN_SIZE = CW_USEDEFAULT;

	constexpr INT SYS_CURSOR_ARROW = 32512;
	constexpr INT SYS_CURSOR_TEXT_SELECT = 32513;
	constexpr INT SYS_CURSOR_WAIT = 32514;
	constexpr INT SYS_CURSOR_CROSS = 32515;
	constexpr INT SYS_CURSOR_UP_ARROW = 32516;
	constexpr INT SYS_CURSOR_HANDWRITING = 32631;
	constexpr INT SYS_CURSOR_SIZE_NW_SE = 32642;
	constexpr INT SYS_CURSOR_SIZE_NE_SW = 32643;
	constexpr INT SYS_CURSOR_SIZE_WE = 32644;
	constexpr INT SYS_CURSOR_SIZE_NS = 32645;
	constexpr INT SYS_CURSOR_SIZE_ALL = 32646;
	constexpr INT SYS_CURSOR_NO = 32648;
	constexpr INT SYS_CURSOR_HAND = 32649;
	constexpr INT SYS_CURSOR_APP_STARTING = 32650;
	constexpr INT SYS_CURSOR_APP_HELP = 32651;
	constexpr INT SYS_CURSOR_APP_PIN = 32671;
	constexpr INT SYS_CURSOR_APP_PERSON = 32672;

	constexpr INT SYS_ICON_APPLICATION = 32512;
	constexpr INT SYS_ICON_ERROR = 32513;
	constexpr INT SYS_ICON_QUESTION = 32514;
	constexpr INT SYS_ICON_WARNING = 32515;
	constexpr INT SYS_ICON_INFORMATION = 32516;
	constexpr INT SYS_ICON_SHIELD = 32518;
}
