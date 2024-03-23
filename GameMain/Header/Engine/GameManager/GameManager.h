#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	class GameObject;
	class GameManager
	{
	public:
		static void ProcessMousePosition(Point position);

		static void ProcessKeyDownInput(KeyCode keyCode);
		static void ProcessKeyUpInput(KeyCode keyCode);
		static void ProcessMouseKeyDownInput(MouseKeyCode mouseKeyCode);
		static void ProcessMouseKeyUpInput(MouseKeyCode mouseKeyCode);

		static void ClearKeyDownUp();
		static void ClearMouseKeyDownUp();
		static void ResetMouseKeyUp();

		static void ProcessMainAspect(FLOAT aspect);
		static void ProcessTime(DOUBLE nowTime);

		static const std::unordered_map<Material*, std::vector<GameObject*>>& GetMatGoMap();
		static void SetMatGoMap(const std::unordered_map<Material*, std::vector<GameObject*>>& matGoMap);

	private:
		static std::unordered_map<Material*, std::vector<GameObject*>> sm_materialList;
	};
}
