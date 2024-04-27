#pragma once

#include <map>
#include "../Component/EngineComponent/Actor/Actor.h"

namespace XusoryEngine
{
	class Behaviour;
	class Component;
	class Transform;
	DLL_CLASS(GameObject)
	{
	public:
		GameObject();
		explicit GameObject(const std::string_view& name);
		explicit GameObject(const Vector3& localPosition);
		explicit GameObject(const Vector3& localPosition, const Vector3& localScale, const Vector3& localEulerAngle);
		DELETE_COPY_OPERATOR(GameObject);
		DELETE_MOVE_OPERATOR(GameObject);
		~GameObject();

		BOOL CompareTag(const std::string_view& otherTag) const;
		BOOL GetActive() const;
		void SetActive(BOOL active);

		GameObject* GetParent() const;
		GameObject* GetRootParent() const;
		BOOL HasParent() const;
		void SetParent(GameObject* parent);

		UINT GetChildrenCount() const;
		GameObject* GetChildByIndex(UINT index) const;
		GameObject* GetChildByName(const std::string_view& name, BOOL throwIfNotFound = false) const;
		void AddChildGameObject(GameObject* child);
		void MoveChildGameObject(UINT indexFrom, UINT indexTo);

		GameObject* GetSameLevelObjectByIndex(UINT index) const;
		GameObject* GetSameLevelObjectByName(const std::string_view& name, BOOL throwIfNotFound = false) const;

		Transform* GetTransform() const;
		const std::multimap<std::string, Actor*>& GetActorMap() const;

		template <typename T>
		T* AddComponent();
		template <typename T>
		BOOL HasComponent();
		template <typename T>
		void RemoveComponent();
		void RemoveAllComponent();

		template <typename T>
		T* GetComponent();
		template <typename T>
		T* GetComponentInParent();
		template <typename T>
		T* GetComponentInChildren(UINT index);
		template <typename T>
		T* GetComponentInChildren(const std::string_view& name, BOOL throwIfNotFound = false);

		template <typename T>
		std::vector<T*> GetComponents();
		template <typename T>
		std::vector<T*> GetComponentsInParent();
		template <typename T>
		std::vector<T*> GetComponentsInChildren(UINT index);
		template <typename T>
		std::vector<T*> GetComponentsInChildren(const std::string_view& name, BOOL throwIfNotFound = false);

		static GameObject* FindGameObjectByName(const std::string_view & name, UINT count = 0);
		static void Destroy(GameObject*& gameObject);

		std::string name;
		std::string tag = "UnDefined";

		UINT instanceId = 0;
		UINT layer = 0;

	private:
		void InitGameObject() const;
		void RemoveChildGameObject(const GameObject* child, BOOL throwIfNotFound = false);

		BOOL m_active = true;

		GameObject* m_parent = nullptr;
		std::vector<GameObject*> m_childrenList;

		std::unique_ptr<Transform> m_transform;
		std::multimap<std::string, Actor*> m_actorMap;
		std::multimap<std::string, std::unique_ptr<Behaviour>> m_behaviourMap;
	};

	template<typename T>
	T* GameObject::AddComponent()
	{
		static_assert(std::is_base_of_v<Behaviour, T>);

		const std::string typeName = GetTypeName<T>();

		T* behaviour = new T(typeName, this);
		m_behaviourMap.emplace(typeName, behaviour);

		if (std::is_base_of_v<Actor, T>)
		{
			auto* actor = reinterpret_cast<Actor*>(behaviour);
			actor->OnAwake();
			actor->OnEnable();

			m_actorMap.emplace(typeName, actor);
		}

		return behaviour;
	}

	template<typename T>
	BOOL GameObject::HasComponent()
	{
		static_assert(std::is_base_of_v<Behaviour, T>);
		CaptureNoReturnFunc(return m_behaviourMap.find(GetTypeName<T>()) != m_behaviourMap.end());
	}

	template<typename T>
	void GameObject::RemoveComponent()
	{
		static_assert(std::is_base_of_v<Behaviour, T>);
		const std::string typeName = GetTypeName<T>();

		T* behaviour = GetComponent<T>();
		if (std::is_base_of_v<Actor, T>)
		{
			auto* actor = reinterpret_cast<Actor*>(behaviour);
			actor->OnDisable();
			actor->OnDestroy();

			m_actorMap.erase(typeName);
		}
		m_behaviourMap.erase(typeName);
	}

	template<typename T>
	T* GameObject::GetComponent()
	{
		static_assert(std::is_base_of_v<Behaviour, T>);

		CaptureNoReturnFunc(auto it = m_behaviourMap.find(GetTypeName<T>()));
		if (it != m_behaviourMap.end())
		{
			return static_cast<T*>(it->second.get());
		}
		return nullptr;
	}

	template<typename T>
	T* GameObject::GetComponentInParent()
	{
		if (m_parent == nullptr)
		{
			ThrowWithErrName(RuntimeError, "parent is nullptr");
		}
		return m_parent->GetComponent<T>();
	}

	template<typename T>
	T* GameObject::GetComponentInChildren(UINT index)
	{
		return GetChildByIndex(index)->GetComponent<T>();
	}

	template<typename T>
	T* GameObject::GetComponentInChildren(const std::string_view& name, BOOL throwIfNotFound)
	{
		return GetChildByName(name, throwIfNotFound)->GetComponent<T>();
	}

	template<typename T>
	std::vector<T*> GameObject::GetComponents()
	{
		static_assert(std::is_base_of_v<Behaviour, T>);
		std::vector<T*> componentListTemp;

		auto range = m_behaviourMap.equal_range(GetTypeName<T>());
		for (auto i = range.first; i != range.second; ++i)
		{
			componentListTemp.push_back(i->second.get());
		}

		return componentListTemp;
	}

	template<typename T>
	std::vector<T*> GameObject::GetComponentsInParent()
	{
		if (m_parent == nullptr)
		{
			ThrowWithErrName(RuntimeError, "parent is nullptr");
		}
		return m_parent->GetComponents<T>();
	}

	template<typename T>
	std::vector<T*> GameObject::GetComponentsInChildren(UINT index)
	{
		return GetChildByIndex(index)->GetComponents<T>();
	}

	template<typename T>
	std::vector<T*> GameObject::GetComponentsInChildren(const std::string_view& name, BOOL throwIfNotFound)
	{
		return GetChildByName(name, throwIfNotFound)->GetComponents<T>();
	}
}
