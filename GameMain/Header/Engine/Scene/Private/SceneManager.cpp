#include "../SceneManager.h"
#include "../Scene.h"

namespace XusoryEngine
{
	Scene* SceneManager::sm_activeScene = nullptr;

	Scene* SceneManager::GetActiveScene()
	{
		return sm_activeScene;
	}

	void SceneManager::LoadScene(const std::wstring_view& path)
	{
		sm_activeScene = new Scene();
	}
}
