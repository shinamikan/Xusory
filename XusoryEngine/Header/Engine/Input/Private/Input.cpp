#include "../Input.h"

namespace XusoryEngine
{
	std::unordered_map<std::string, KeyCode> Input::sm_buttonKeyCodeMap = std::unordered_map<std::string, KeyCode>();

	std::unordered_set<KeyCode> Input::sm_keyCodeSet = std::unordered_set<KeyCode>();
	std::unordered_set<KeyCode> Input::sm_keyCodeDownSet = std::unordered_set<KeyCode>();
	std::unordered_set<KeyCode> Input::sm_keyCodeUpSet = std::unordered_set<KeyCode>();

	UINT Input::sm_mouseKeyCode = 0;
	UINT Input::sm_mouseKeyDownCode = 0;
	UINT Input::sm_mouseKeyUpCode = 0;
	BOOL Input::sm_mouseUpFlag = false;

	INT16 Input::sm_mouseWheelDistance = 0;
	Point Input::sm_mousePosition = { 0, 0 };

	BOOL Input::GetButton(const std::string_view& buttonName)
	{
		CaptureNoReturnFunc(const auto keyCode = sm_buttonKeyCodeMap.at(buttonName.data()));
		return sm_keyCodeSet.find(keyCode) != sm_keyCodeSet.end();
	}

	BOOL Input::GetButtonDown(const std::string_view& buttonName)
	{
		CaptureNoReturnFunc(const auto keyCode = sm_buttonKeyCodeMap.at(buttonName.data()));
		return sm_keyCodeDownSet.find(keyCode) != sm_keyCodeDownSet.end();
	}

	BOOL Input::GetButtonUp(const std::string_view& buttonName)
	{
		CaptureNoReturnFunc(const auto keyCode = sm_buttonKeyCodeMap.at(buttonName.data()));
		return sm_keyCodeUpSet.find(keyCode) != sm_keyCodeUpSet.end();
	}

	void Input::SetButton(const std::string_view& buttonName, KeyCode keyCode)
	{
		sm_buttonKeyCodeMap.emplace(buttonName.data(), keyCode);
	}

	BOOL Input::GetKey(KeyCode keyCode)
	{
		return sm_keyCodeSet.find(keyCode) != sm_keyCodeSet.end();
	}

	BOOL Input::GetKeyDown(KeyCode keyCode)
	{
		return sm_keyCodeDownSet.find(keyCode) != sm_keyCodeDownSet.end();
	}

	BOOL Input::GetKeyUp(KeyCode keyCode)
	{
		return sm_keyCodeUpSet.find(keyCode) != sm_keyCodeUpSet.end();
	}

	BOOL Input::GetMouseKey(MouseKeyCode mouseKeyCode)
	{
		switch (mouseKeyCode)
		{
		case MouseKeyCode::LEFT:
			return Math::IsBitSet(sm_mouseKeyCode, 0);

		case MouseKeyCode::RIGHT:
			return Math::IsBitSet(sm_mouseKeyCode, 1);

		case MouseKeyCode::MID:
			return Math::IsBitSet(sm_mouseKeyCode, 4);

		case MouseKeyCode::EX_1:
			return Math::IsBitSet(sm_mouseKeyCode, 5);

		case MouseKeyCode::EX_2:
			return Math::IsBitSet(sm_mouseKeyCode, 6);
		}

		return false;
	}

	BOOL Input::GetMouseKeyDown(MouseKeyCode mouseKeyCode)
	{
		switch (mouseKeyCode)
		{
		case MouseKeyCode::LEFT:
			return Math::IsBitSet(sm_mouseKeyDownCode, 0);

		case MouseKeyCode::RIGHT:
			return Math::IsBitSet(sm_mouseKeyDownCode, 1);

		case MouseKeyCode::MID:
			return Math::IsBitSet(sm_mouseKeyDownCode, 4);

		case MouseKeyCode::EX_1:
			return Math::IsBitSet(sm_mouseKeyDownCode, 5);

		case MouseKeyCode::EX_2:
			return Math::IsBitSet(sm_mouseKeyDownCode, 6);
		}

		return false;
	}

	BOOL Input::GetMouseKeyUp(MouseKeyCode mouseKeyCode)
	{
		if (!sm_mouseUpFlag)
		{
			return false;
		}

		BOOL result = false;
		switch (mouseKeyCode)
		{
		case MouseKeyCode::LEFT:
			result = Math::IsBitSet(sm_mouseKeyCode, 0) != Math::IsBitSet(sm_mouseKeyUpCode, 0);
			break;

		case MouseKeyCode::RIGHT:
			result = Math::IsBitSet(sm_mouseKeyCode, 1) != Math::IsBitSet(sm_mouseKeyUpCode, 1);
			break;

		case MouseKeyCode::MID:
			result = Math::IsBitSet(sm_mouseKeyCode, 4) != Math::IsBitSet(sm_mouseKeyUpCode, 4);
			break;

		case MouseKeyCode::EX_1:
			result = Math::IsBitSet(sm_mouseKeyCode, 5) != Math::IsBitSet(sm_mouseKeyUpCode, 5);
			break;

		case MouseKeyCode::EX_2:
			result = Math::IsBitSet(sm_mouseKeyCode, 6) != Math::IsBitSet(sm_mouseKeyUpCode, 6);
			break;
		}

		return result;
	}

	INT16 Input::GetMouseWheelDistance()
	{
		return sm_mouseWheelDistance;
	}

	Point Input::GetMousePosition()
	{
		return sm_mousePosition;
	}
}
