#include "../InputDevice.h"

namespace XusoryEngine
{
	BOOL Cursor::sm_isCursorShow = true;
	void Cursor::MoveCursor(INT posX, INT posY)
	{
		SetCursorPos(posX, posY);
	}

	void Cursor::HideCursor()
	{
		if (sm_isCursorShow)
		{
			::ShowCursor(false);
			sm_isCursorShow = false;
		}
	}

	void Cursor::ShowCursor()
	{
		if (!sm_isCursorShow)
		{
			::ShowCursor(true);
			sm_isCursorShow = true;
		}
	}

	void Cursor::VirtualPressMouseKey(MouseEventCode mouseEventCode)
	{
		switch (mouseEventCode)
		{
		case MouseEventCode::LEFT:
			mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
			break;
		case MouseEventCode::RIGHT:
			mouse_event(MOUSEEVENTF_RIGHTDOWN, NULL, NULL, NULL, NULL);
			break;
		case MouseEventCode::MID:
			mouse_event(MOUSEEVENTF_MIDDLEDOWN, NULL, NULL, NULL, NULL);
			break;
		case MouseEventCode::EX1:
			mouse_event(MOUSEEVENTF_XDOWN, NULL, NULL, XBUTTON1, NULL);
			break;
		case MouseEventCode::EX2:
			mouse_event(MOUSEEVENTF_XDOWN, NULL, NULL, XBUTTON2, NULL);
			break;
		}
	}

	void Cursor::VirtualReleaseMouseKey(MouseEventCode mouseEventCode)
	{
		switch (mouseEventCode)
		{
		case MouseEventCode::LEFT:
			mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
			break;
		case MouseEventCode::RIGHT:
			mouse_event(MOUSEEVENTF_RIGHTUP, NULL, NULL, NULL, NULL);
			break;
		case MouseEventCode::MID:
			mouse_event(MOUSEEVENTF_MIDDLEUP, NULL, NULL, NULL, NULL);
			break;
		case MouseEventCode::EX1:
			mouse_event(MOUSEEVENTF_XUP, NULL, NULL, XBUTTON1, NULL);
			break;
		case MouseEventCode::EX2:
			mouse_event(MOUSEEVENTF_XUP, NULL, NULL, XBUTTON2, NULL);
			break;
		}
	}

	void KeyBoard::VirtualClickKey(KeyCode keyCode)
	{
		VirtualPressKey(keyCode);
		VirtualReleaseKey(keyCode);
	}

	void KeyBoard::VirtualPressKey(KeyCode keyCode)
	{
		keybd_event(static_cast<BYTE>(keyCode), NULL, NULL, NULL);
	}

	void KeyBoard::VirtualReleaseKey(KeyCode keyCode)
	{
		keybd_event(static_cast<BYTE>(keyCode), NULL, KEYEVENTF_KEYUP, NULL);
	}
}
