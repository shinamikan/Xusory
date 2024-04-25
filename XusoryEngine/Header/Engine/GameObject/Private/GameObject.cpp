#include "../GameObject.h"
#include "../../Component/Transform/Transform.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneManager.h"

namespace XusoryEngine
{
	GameObject::GameObject() : name("GameObject"), m_transform(new Transform("Transform", this)) { InitGameObject(); }
	GameObject::GameObject(const std::string_view& name) : name(name), m_transform(new Transform("Transform", this)) { InitGameObject(); }
	GameObject::GameObject(const Vector3& localPosition) : m_transform(new Transform("Transform", this, localPosition)) { InitGameObject(); }
	GameObject::GameObject(const Vector3& localPosition, const Vector3& localScale, const Vector3& localEulerAngle) : m_transform(new Transform("Transform", this, localPosition, localScale, localEulerAngle))
	{
		InitGameObject();
	}

	GameObject::~GameObject()
	{
		if (HasParent())
		{
			UINT thisGoIndex = static_cast<UINT>(std::distance(m_childrenList.begin(), std::find(m_parent->m_childrenList.begin(), m_parent->m_childrenList.end(), this)));

			for (auto* child : m_childrenList)
			{
				thisGoIndex++;
				child->SetParent(m_parent);
				m_parent->m_childrenList.insert(m_parent->m_childrenList.begin() + thisGoIndex, child);
			}

			m_parent->m_childrenList.erase(m_parent->m_childrenList.begin() + thisGoIndex);
		}
		else
		{
			Scene* activeScene = SceneManager::GetActiveScene();

			UINT thisGoIndex = static_cast<UINT>(std::distance(activeScene->m_rootGameObjectList.begin(), std::find(activeScene->m_rootGameObjectList.begin(), activeScene->m_rootGameObjectList.end(), this)));
			if (!m_childrenList.empty())
			{
				for (auto* child : m_childrenList)
				{
					thisGoIndex++;
					child->SetParent(nullptr);
					activeScene->m_rootGameObjectList.insert(activeScene->m_rootGameObjectList.begin() + thisGoIndex, child);
				}
			}

			activeScene->m_rootGameObjectList.erase(activeScene->m_rootGameObjectList.begin() + thisGoIndex);
		}

		RemoveAllComponent();
	}

	BOOL GameObject::CompareTag(const std::string_view& otherTag) const
	{
		return tag == otherTag;
	}

	BOOL GameObject::GetActive() const
	{
		return m_active;
	}

	void GameObject::SetActive(BOOL active)
	{
		if (m_active == active)
		{
			return;
		}

		m_active = active;

		for (const auto& actorPair : m_actorMap)
		{
			if (active)
			{
				actorPair.second->OnEnable();
			}
			else
			{
				actorPair.second->OnDisable();
			}
		}
	}

	GameObject* GameObject::GetParent() const
	{
		return m_parent;
	}

	GameObject* GameObject::GetRootParent() const
	{
		if (HasParent())
		{
			return m_parent->GetRootParent();
		}
		return const_cast<GameObject*>(this);
	}

	BOOL GameObject::HasParent() const
	{
		return m_parent != nullptr;
	}

	void GameObject::SetParent(GameObject* parent)
	{
		if (parent == m_parent)
		{
			return;
		}

		Scene* activeScene = SceneManager::GetActiveScene();

		if (parent == nullptr)
		{
			activeScene->AddRootGameObject(this);
			m_parent->RemoveChildGameObject(this);
		}
		else
		{
			if (HasParent())
			{
				m_parent->RemoveChildGameObject(this);
			}
			else
			{
				activeScene->RemoveRootGameObject(this);
			}
			parent->m_childrenList.push_back(this);
		}

		m_parent = parent;
	}

	UINT GameObject::GetChildrenCount() const
	{
		return static_cast<UINT>(m_childrenList.size());
	}

	GameObject* GameObject::GetChildByIndex(UINT index) const
	{
		CaptureNoReturnFunc(return m_childrenList.at(index));
	}

	GameObject* GameObject::GetChildByName(const std::string_view& name, BOOL throwIfNotFound) const
	{
		for (auto* go : m_childrenList)
		{
			if (go->name == name)
			{
				return go;
			}
		}
		if (throwIfNotFound)
		{
			ThrowWithErrName(RuntimeError, "No game object with the specified name was found");
		}
		return nullptr;
	}

	void GameObject::AddChildGameObject(GameObject* child)
	{
		child->SetParent(this);
		//m_childrenList.push_back(child);
	}

	void GameObject::MoveChildGameObject(UINT indexFrom, UINT indexTo)
	{
		if (indexFrom == indexTo)
		{
			return;
		}

		CaptureNoReturnFunc(GameObject* childTemp = m_childrenList.at(indexFrom));

		if (indexFrom < indexTo)
		{
			const auto insertIt = m_childrenList.begin() + indexTo + 1;
			CaptureNoReturnFunc(m_childrenList.insert(insertIt, childTemp));

			const auto childIt = m_childrenList.begin() + indexFrom;
			CaptureNoReturnFunc(m_childrenList.erase(childIt));
		}
		else
		{
			const auto childIt = m_childrenList.begin() + indexFrom;
			CaptureNoReturnFunc(m_childrenList.erase(childIt));

			const auto insertIt = m_childrenList.begin() + indexTo;
			CaptureNoReturnFunc(m_childrenList.insert(insertIt, childTemp));
		}
	}

	GameObject* GameObject::GetSameLevelObjectByIndex(UINT index) const
	{
		if (HasParent())
		{
			return m_parent->GetChildByIndex(index);
		}

		const auto* scene = SceneManager::GetActiveScene();
		return scene->GetRootGameObject(index);
	}

	GameObject* GameObject::GetSameLevelObjectByName(const std::string_view& name, BOOL throwIfNotFound) const
	{
		if (!HasParent())
		{
			const auto* activeScene = SceneManager::GetActiveScene();
			for (auto* go : activeScene->m_rootGameObjectList)
			{
				if (go->name == name)
				{
					return go;
				}
			}
		}

		for (auto* go : m_childrenList)
		{
			if (go->name == name)
			{
				return go;
			}
		}

		if (throwIfNotFound)
		{
			ThrowWithErrName(RuntimeError, "No game object with the specified name was found");
		}
		return nullptr;
	}

	Transform* GameObject::GetTransform() const
	{
		return m_transform.get();
	}

	const std::multimap<std::string, Actor*>& GameObject::GetActorMap() const
	{
		return m_actorMap;
	}

	void GameObject::RemoveAllComponent()
	{
		for (const auto& actorPair : m_actorMap)
		{
			actorPair.second->OnDisable();
			actorPair.second->OnDestroy();
		}
		m_actorMap.clear();
		m_behaviourMap.clear();
	}

	GameObject* GameObject::FindGameObjectByName(const std::string_view& name, UINT count)
	{
		for (auto* gameObject : SceneManager::GetActiveScene()->GetGameObjectList())
		{
			if (gameObject->name == name)
			{
				return gameObject;
			}
		}

		return nullptr;
	}

	void GameObject::Destroy(GameObject*& gameObject)
	{
		if (gameObject != nullptr)
		{
			delete gameObject;
			gameObject = nullptr;
		}
	}

	void GameObject::InitGameObject() const
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		activeScene->AddRootGameObject(this);
	}

	void GameObject::RemoveChildGameObject(const GameObject* child, BOOL throwIfNotFound)
	{
		const auto childGoIt = std::find(m_childrenList.begin(), m_childrenList.end(), child);

		if (childGoIt != m_childrenList.end())
		{
			m_childrenList.erase(childGoIt);
		}
		if (throwIfNotFound)
		{
			ThrowWithErrName(RuntimeError, "No game object was found");
		}
	}
}
