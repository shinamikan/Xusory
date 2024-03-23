#pragma once

#include <list>
#include <vector>
#include "../../Core/Core.h"

namespace XusoryEngine
{
	class Actor;
	class GameObject;
	class Scene
	{
		friend class GameObject;

	public:
		Scene() = default;

		UINT GetRootGameObjectCount() const;
		GameObject* GetRootGameObject(UINT index) const;

		std::vector<GameObject*> GetSceneGameObjectList() const;
		std::unordered_map<Material*, std::vector<GameObject*>> GetSceneMatGoMap() const;

		void AddRootGameObject(const GameObject* gameObject);
		void MoveRootGameObject(UINT indexFrom, UINT indexTo);

		std::string name;
		std::string sceneFilePath;

	private:
		void RemoveRootGameObject(const GameObject* gameObject, BOOL throwIfNotFound = false);

		std::vector<GameObject*> m_rootGameObjectList;
	};
}
