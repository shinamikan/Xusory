#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	class GameObject;
	DLL_STATIC_CLASS(GameManager)
	{
	public:
		static void ProcessMousePosition(Point position);
		static void ProcessMouseWheel(INT16 distance);

		static void ProcessKeyDownInput(KeyCode keyCode);
		static void ProcessKeyUpInput(KeyCode keyCode);
		static void ProcessMouseKeyDownInput(MouseKeyCode mouseKeyCode);
		static void ProcessMouseKeyUpInput(MouseKeyCode mouseKeyCode);

		static void ClearKeyDownUp();
		static void ClearMouseKeyDownUp();
		static void ClearMouseWheel();
		static void ResetMouseKeyUp();

		static void ProcessMainAspect(FLOAT aspect);
		static void ProcessTime(DOUBLE nowTime);
	};
}
