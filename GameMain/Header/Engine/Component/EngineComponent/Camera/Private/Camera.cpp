#include "../Camera.h"
#include "../../../Transform/Transform.h"
#include "../../../../GameObject/GameObject.h"

namespace XusoryEngine
{
	INIT_XS_CLASS(Camera);

	Matrix4x4 Camera::GetViewMatrix() const
	{
		const Vector3& cameraPosition = m_belongsGameObject->GetTransform()->GetPositionVector();
		const Vector3& worldUpDirection = Vector3(0.0f, 1.0f, 0.0f);

		const Vector3 forward = (targetPosition - cameraPosition).Normalize();
		const Vector3 right = Vector3::Cross(worldUpDirection, forward).Normalize();
		const Vector3 upDirection = Vector3::Cross(forward, right);

		return {
			right.X(), upDirection.X(), forward.X(), 0.0f,
			right.Y(), upDirection.Y(), forward.Y(), 0.0f,
			right.Z(), upDirection.Z(), forward.Z(), 0.0f,
			-right.Dot(cameraPosition), -upDirection.Dot(cameraPosition), -forward.Dot(cameraPosition), 1.0f
		};
	}

	Matrix4x4 Camera::GetProjectionMatrix() const
	{
		const FLOAT fovAngle = Math::DegreeToRadian(fieldOfView);

		return {
			1.0f / (aspect * std::tan(fovAngle / 2)), 0.0f, 0.0f, 0.0f,
			0.0f, 1 / std::tan(fovAngle / 2), 0.0f, 0.0f,
			0.0f, 0.0f, farPlane / (farPlane - nearPlane), 1.0f,
			0.0f, 0.0f, -farPlane * nearPlane / (farPlane - nearPlane), 0.0f
		};
	}

	Camera* Camera::mainCamera = nullptr;
}
