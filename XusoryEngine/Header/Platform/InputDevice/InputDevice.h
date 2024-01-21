#pragma once

#include "../Common/PlatformDefine.h"
#include "Commom/KeyCode.h"

namespace XusoryEngine
{
	enum MouseEventCode
	{
		MOUSE_LEFT,
		MOUSE_RIGHT,
		MOUSE_MID,
		MOUSE_EX1,
		MOUSE_EX2,
	};

	DLL_STATIC_CLASS(Cursor)
	{
	public:
		static void MoveCursor(INT posX, INT posY);
		static void HideCursor();
		static void ShowCursor();

		static void VirtualPressMouseKey(MouseEventCode mouseEventCode);
		static void VirtualReleaseMouseKey(MouseEventCode mouseEventCode);

	private:
		static BOOL sm_isCursorShow;
	};

	DLL_STATIC_CLASS(KeyBoard)
	{
	public:
		static void VirtualClickKey(KeyCode keyCode);
		static void VirtualPressKey(KeyCode keyCode);
		static void VirtualReleaseKey(KeyCode keyCode);
	};
}
