#include "../GameObject.h"
#include "../../Component/Transform/Transform.h"

namespace XusoryEngine
{
	GameObject::GameObject() : name("GameObject"), m_transform(new Transform("Transform", this)) { }
	GameObject::GameObject(const std::string_view& name) : name(name), m_transform(new Transform("Transform", this)) { }
	GameObject::GameObject(const Float3& localPosition) : m_transform(new Transform("Transform", this, localPosition)) { }
	GameObject::GameObject(const Float3& localPosition, const Float3& localScale) : m_transform(new Transform("Transform", this, localPosition, localScale)) { }
	GameObject::GameObject(const std::string_view& name, const Float3& localPosition) : name(name), m_transform(new Transform("Transform", this, localPosition)) { }
	GameObject::GameObject(const std::string_view& name, const Float3& localPosition, const Float3& localScale) : name(name), m_transform(new Transform("Transform", this, localPosition, localScale)) { }

	GameObject::~GameObject()
	{
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

	Transform* GameObject::GetTransform() const
	{
		return m_transform.get();
	}

	const std::multimap<std::string, Actor*>& GameObject::GetActorMap()
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
}
