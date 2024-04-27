#pragma once

#include "../Common/EngineDefine.h"

namespace XusoryEngine
{
	class GameObject;
	DLL_CLASS(Component)
	{
		friend class GameObject;

	public:
		DELETE_COPY_OPERATOR(Component);
		DELETE_MOVE_OPERATOR(Component);
		virtual ~Component() = default;

		const std::string& GetComponentName() const;
		BOOL CompareTag(const std::string_view& otherTag) const;

		GameObject* belongsGameObject = nullptr;

	protected:
		explicit Component(const std::string_view& componentName, GameObject* gameObject);

	private:
		std::string m_componentName;
	};
}
