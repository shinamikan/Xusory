#include "../Light.h"
#include "../../../../GameObject/GameObject.h"
#include "../../../Transform/Transform.h"

namespace XusoryEngine
{
	INIT_XS_CLASS(Light);

	Vector3 Light::ambient = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 Light::GetLightWorldPosition() const
	{
		return m_belongsGameObject->GetTransform()->GetPosition(Space::WORLD);
	}

	Vector3 Light::GetLightWorldDirection() const
	{
		return m_belongsGameObject->GetTransform()->Forward();
	}

}
