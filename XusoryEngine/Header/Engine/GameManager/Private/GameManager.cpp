#include "../GameManager.h"
#include "../../Component/EngineComponent/Camera/Camera.h"
#include "../../GameTimer/GameTimer.h"
#include "../../Input/Input.h"

namespace XusoryEngine
{
	void GameManager::ProcessMousePosition(Point position)
	{
		Input::sm_mousePosition = position;
	}

	void GameManager::ProcessMouseWheel(INT16 distance)
	{
		Input::sm_mouseWheelDistance = distance;
	}

	void GameManager::ProcessKeyDownInput(KeyCode keyCode)
	{
		if (Input::sm_keyCodeSet.find(keyCode) == Input::sm_keyCodeSet.end())
		{
			Input::sm_keyCodeSet.emplace(keyCode);
			Input::sm_keyCodeDownSet.emplace(keyCode);
		}
	}

	void GameManager::ProcessKeyUpInput(KeyCode keyCode)
	{
		CaptureNoReturnFunc(Input::sm_keyCodeSet.erase(keyCode));
		Input::sm_keyCodeUpSet.emplace(keyCode);
	}

	void GameManager::ProcessMouseKeyDownInput(MouseKeyCode mouseKeyCode)
	{
		Input::sm_mouseKeyCode = static_cast<UINT>(mouseKeyCode);
		Input::sm_mouseKeyDownCode = static_cast<UINT>(mouseKeyCode);
	}

	void GameManager::ProcessMouseKeyUpInput(MouseKeyCode mouseKeyCode)
	{
		Input::sm_mouseKeyUpCode = static_cast<UINT>(mouseKeyCode);
		Input::sm_mouseUpFlag = true;
	}

	void GameManager::ClearKeyDownUp()
	{
		Input::sm_keyCodeDownSet.clear();
		Input::sm_keyCodeUpSet.clear();
	}

	void GameManager::ClearMouseKeyDownUp()
	{
		Input::sm_mouseKeyDownCode = 0;
		Input::sm_mouseKeyUpCode = 0;
	}

	void GameManager::ClearMouseWheel()
	{
		Input::sm_mouseWheelDistance = 0;
	}

	void GameManager::ResetMouseKeyUp()
	{
		if (Input::sm_mouseUpFlag)
		{
			Input::sm_mouseKeyCode = Input::sm_mouseKeyUpCode;
			Input::sm_mouseUpFlag = false;
		}
	}

	void GameManager::ProcessMainAspect(FLOAT aspect)
	{
		Camera::mainCamera->aspect = aspect;
	}

	void GameManager::ProcessTime(DOUBLE nowTime)
	{
		if (!GameTimer::sm_isInit)
		{
			GameTimer::sm_lastRealTime = nowTime;
			GameTimer::sm_isInit = true;

			return;
		}

		GameTimer::sm_lastTime = GameTimer::sm_time;

		GameTimer::sm_time += nowTime - GameTimer::sm_lastRealTime;
		GameTimer::sm_lastRealTime = nowTime;
	}
}
