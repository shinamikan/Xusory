#pragma once

#include "../Common/EngineDefine.h"

namespace XusoryEngine
{
	class GameObject;
	class Component
	{
		friend class GameObject;

	public:
		DELETE_COPY_OPERATOR(Component);
		DELETE_MOVE_OPERATOR(Component);
		virtual ~Component() = default;

		const std::string& GetComponentName() const;
		BOOL CompareTag(const std::string_view& otherTag) const;

	protected:
		explicit Component(const std::string_view& componentName, GameObject* gameObject);
		GameObject* m_belongsGameObject = nullptr;

	private:
		std::string m_componentName;
	};
}
