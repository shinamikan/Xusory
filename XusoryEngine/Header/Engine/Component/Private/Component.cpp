#include "../Component.h"
#include "../../GameObject/GameObject.h"

namespace XusoryEngine
{
	const std::string& Component::GetComponentName() const
	{
		return m_componentName;
	}

	BOOL Component::CompareTag(const std::string_view& otherTag) const
	{
		return belongsGameObject->CompareTag(otherTag);
	}

	Component::Component(const std::string_view& componentName, GameObject* gameObject)
		: belongsGameObject(gameObject), m_componentName(componentName) { }
}
