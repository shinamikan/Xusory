#include "../Camera.h"
#include "../../../Transform/Transform.h"
#include "../../../../GameObject/GameObject.h"

namespace XusoryEngine
{
	INIT_XS_CLASS(Camera);

	Camera* Camera::mainCamera = nullptr;
	FLOAT Camera::GetAspect() const
	{
		return aspect;
	}

	Matrix4x4 Camera::GetViewMatrix() const
	{
		const Vector3 cameraPosition = m_belongsGameObject->GetTransform()->GetPosition(Space::WORLD);

		const Vector3 up = m_belongsGameObject->GetTransform()->Up().Normalize();
		const Vector3 forward = m_belongsGameObject->GetTransform()->Forward().Normalize();
		const Vector3 right = m_belongsGameObject->GetTransform()->Right().Normalize();

		return {
			right.X(), up.X(), forward.X(), 0.0f,
			right.Y(), up.Y(), forward.Y(), 0.0f,
			right.Z(), up.Z(), forward.Z(), 0.0f,
			-right.Dot(cameraPosition), -up.Dot(cameraPosition), -forward.Dot(cameraPosition), 1.0f
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
}
