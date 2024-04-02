#include <functional>
#include "../Scene.h"

#include "../../Component/EngineComponent/Renderer/MeshRenderer.h"
#include "../../GameObject/GameObject.h"

namespace XusoryEngine
{
	UINT Scene::GetRootGameObjectCount() const
	{
		return static_cast<UINT>(m_rootGameObjectList.size());
	}

	GameObject* Scene::GetRootGameObject(UINT index) const
	{
		CaptureNoReturnFunc(return m_rootGameObjectList.at(index));
	}

	std::vector<GameObject*> Scene::GetGameObjectList()
	{
		if (!m_isGameObjectListDirty)
		{
			return m_gameObjectList;
		}

		m_gameObjectList.clear();
		std::function<void(GameObject*)> addAllChildrenToGoList = [&](GameObject* gameObject)
		{
			m_gameObjectList.push_back(gameObject);

			for (UINT i = 0; i < gameObject->GetChildrenCount(); i++)
			{
				addAllChildrenToGoList(gameObject->GetChildByIndex(i));
			}
		};

		for (auto* rootGameObject : m_rootGameObjectList)
		{
			addAllChildrenToGoList(rootGameObject);
		}

		m_isGameObjectListDirty = false;
		return m_gameObjectList;
	}

	std::unordered_map<Material*, std::vector<GameObject*>> Scene::GetMatGoMap()
	{
		if (!m_isMatGoMapDirty)
		{
			return m_matGoMapTemp;
		}

		m_matGoMapTemp.clear();
		std::function<void(GameObject*)> addAllChildrenToMatGoMap = [&](GameObject* gameObject)
		{
			if (gameObject->HasComponent<MeshRenderer>())
			{
				const MeshRenderer* renderer = gameObject->GetComponent<MeshRenderer>();
				if (Material* material = renderer->GetMaterial(); material != nullptr)
				{
					if (m_matGoMapTemp.find(material) == m_matGoMapTemp.end())
					{
						m_matGoMapTemp.emplace(material, 0);
					}

					auto& goList = m_matGoMapTemp.at(material);
					goList.push_back(gameObject);
				}
			}

			for (UINT i = 0; i < gameObject->GetChildrenCount(); i++)
			{
				addAllChildrenToMatGoMap(gameObject->GetChildByIndex(i));
			}
		};

		for (auto* rootGameObject : m_rootGameObjectList)
		{
			addAllChildrenToMatGoMap(rootGameObject);
		}

		m_isMatGoMapDirty = false;
		return m_matGoMapTemp;
	}

	void Scene::AddRootGameObject(const GameObject* gameObject)
	{
		m_isGameObjectListDirty = true;
		m_rootGameObjectList.push_back(const_cast<GameObject*>(gameObject));
	}

	void Scene::MoveRootGameObject(UINT indexFrom, UINT indexTo)
	{
		if (indexFrom == indexTo)
		{
			return;
		}

		CaptureNoReturnFunc(GameObject* childTemp = m_rootGameObjectList.at(indexFrom));

		if (indexFrom < indexTo)
		{
			const auto insertIt = m_rootGameObjectList.begin() + indexTo + 1;
			CaptureNoReturnFunc(m_rootGameObjectList.insert(insertIt, childTemp));

			const auto childIt = m_rootGameObjectList.begin() + indexFrom;
			CaptureNoReturnFunc(m_rootGameObjectList.erase(childIt));
		}
		else
		{
			const auto childIt = m_rootGameObjectList.begin() + indexFrom;
			CaptureNoReturnFunc(m_rootGameObjectList.erase(childIt));

			const auto insertIt = m_rootGameObjectList.begin() + indexTo;
			CaptureNoReturnFunc(m_rootGameObjectList.insert(insertIt, childTemp));
		}
	}

	void Scene::RemoveRootGameObject(const GameObject* gameObject, BOOL throwIfNotFound)
	{
		const auto goIt = std::find(m_rootGameObjectList.begin(), m_rootGameObjectList.end(), gameObject);

		if (goIt != m_rootGameObjectList.end())
		{
			m_rootGameObjectList.erase(goIt);
		}
		if (throwIfNotFound)
		{
			ThrowWithErrName(RuntimeError, "No game object was found");
		}
	}
}
