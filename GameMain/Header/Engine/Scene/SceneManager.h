#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	class Scene;
	class SceneManager
	{
	public:
		static Scene* GetActiveScene();
		static void LoadScene(const std::wstring_view& path);

	private:
		static Scene* sm_activeScene;
	};
}
