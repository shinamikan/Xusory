#pragma once

#include <unordered_map>
#include <unordered_set>

#include "../../Core/Core.h"

namespace XusoryEngine
{
	DLL_STATIC_CLASS(Input)
	{
		friend class GameManager;

	public:
		static BOOL GetButton(const std::string_view & buttonName);
		static BOOL GetButtonDown(const std::string_view & buttonName);
		static BOOL GetButtonUp(const std::string_view & buttonName);

		static void SetButton(const std::string_view & buttonName, KeyCode keyCode);

		static BOOL GetKey(KeyCode keyCode);
		static BOOL GetKeyDown(KeyCode keyCode);
		static BOOL GetKeyUp(KeyCode keyCode);

		static BOOL GetMouseKey(MouseKeyCode mouseKeyCode);
		static BOOL GetMouseKeyDown(MouseKeyCode mouseKeyCode);
		static BOOL GetMouseKeyUp(MouseKeyCode mouseKeyCode);

		static INT16 GetMouseWheelDistance();
		static Point GetMousePosition();

	private:
		static std::unordered_map<std::string, KeyCode> sm_buttonKeyCodeMap;

		static std::unordered_set<KeyCode> sm_keyCodeSet;
		static std::unordered_set<KeyCode> sm_keyCodeDownSet;
		static std::unordered_set<KeyCode> sm_keyCodeUpSet;

		static UINT sm_mouseKeyCode;
		static UINT sm_mouseKeyDownCode;
		static UINT sm_mouseKeyUpCode;
		static BOOL sm_mouseUpFlag;

		static INT16 sm_mouseWheelDistance;
		static Point sm_mousePosition;
	};
}
