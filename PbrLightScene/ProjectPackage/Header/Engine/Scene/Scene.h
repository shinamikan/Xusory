#pragma once

#include <array>
#include <vector>
#include "../../Core/Core.h"

namespace XusoryEngine
{
	class Actor;
	class GameObject;
	class Light;
	DLL_CLASS(Scene)
	{
		friend class GameObject;
		friend class MeshRenderer;

	public:
		Scene() = default;

		UINT GetRootGameObjectCount() const;
		GameObject* GetRootGameObject(UINT index) const;

		std::vector<GameObject*> GetGameObjectList();
		std::unordered_map<Material*, std::vector<GameObject*>> GetMatGoMap();

		void AddRootGameObject(const GameObject* gameObject);
		void MoveRootGameObject(UINT indexFrom, UINT indexTo);

		std::string name;
		std::string sceneFilePath;

		Light* globalLight;

	private:
		void RemoveRootGameObject(const GameObject* gameObject, BOOL throwIfNotFound = false);

		std::vector<GameObject*> m_gameObjectList;
		BOOL m_isGameObjectListDirty = false;

		std::unordered_map<Material*, std::vector<GameObject*>> m_matGoMapTemp;
		BOOL m_isMatGoMapDirty = false;

		std::vector<GameObject*> m_rootGameObjectList;
	};
}
