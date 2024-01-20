#pragma once

#include "../../InputDevice/Commom/KeyCode.h"

namespace XusoryEngine
{
	enum FocusReason
	{
		MOUSE_CLICK = WA_CLICKACTIVE,
		KEY_OR_FUNCTION = WA_ACTIVE
	};

	struct FocusEvent
	{
		FocusReason focusReason;
	};

	struct MoveEvent
	{
		INT16 movePosX;
		INT16 movePosY;
	};

	struct ResizeEvent
	{
		INT16 sizeX;
		INT16 sizeY;
	};

	struct MouseMoveEvent
	{
		INT16 mouseMovePosX;
		INT16 mouseMovePosY;
	};

	struct MouseClickEvent
	{
		MouseKeyCode mouseKeyCode;
		INT16 clickPosX;
		INT16 clickPosY;
	};

	struct MouseWheelEvent
	{
		INT16 mouseWheelDis;
	};

	struct KeyEvent
	{
		KeyCode keyCode;
		BOOL isRepeating;
	};
}
