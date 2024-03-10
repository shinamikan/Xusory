#include "../Camera.h"
#include "../../../Transform/Transform.h"
#include "../../../../GameObject/GameObject.h"
#include "../../../../EngineMath/EngineMath.h"

namespace XusoryEngine
{
	INIT_XS_CLASS(Camera);

	Matrix4x4 Camera::GetViewMatrix() const
	{
		const Vector3& cameraPosition = m_belongsGameObject->GetTransform()->GetPositionVector();
		return EngineMath::BuildViewMatrixLookUp(cameraPosition, targetPosition, Vector3(0.0f, 1.0f, 0.0f));
	}
}
