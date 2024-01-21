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
		case MOUSE_LEFT:
			mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
			break;
		case MOUSE_RIGHT:
			mouse_event(MOUSEEVENTF_RIGHTDOWN, NULL, NULL, NULL, NULL);
			break;
		case MOUSE_MID:
			mouse_event(MOUSEEVENTF_MIDDLEDOWN, NULL, NULL, NULL, NULL);
			break;
		case MOUSE_EX1:
			mouse_event(MOUSEEVENTF_XDOWN, NULL, NULL, XBUTTON1, NULL);
			break;
		case MOUSE_EX2:
			mouse_event(MOUSEEVENTF_XDOWN, NULL, NULL, XBUTTON2, NULL);
			break;
		}
	}

	void Cursor::VirtualReleaseMouseKey(MouseEventCode mouseEventCode)
	{
		switch (mouseEventCode)
		{
		case MOUSE_LEFT:
			mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
			break;
		case MOUSE_RIGHT:
			mouse_event(MOUSEEVENTF_RIGHTUP, NULL, NULL, NULL, NULL);
			break;
		case MOUSE_MID:
			mouse_event(MOUSEEVENTF_MIDDLEUP, NULL, NULL, NULL, NULL);
			break;
		case MOUSE_EX1:
			mouse_event(MOUSEEVENTF_XUP, NULL, NULL, XBUTTON1, NULL);
			break;
		case MOUSE_EX2:
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
		keybd_event(keyCode, NULL, NULL, NULL);
	}

	void KeyBoard::VirtualReleaseKey(KeyCode keyCode)
	{
		keybd_event(keyCode, NULL, KEYEVENTF_KEYUP, NULL);
	}
}
