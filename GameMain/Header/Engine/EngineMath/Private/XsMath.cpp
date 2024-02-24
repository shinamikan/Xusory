#include "../XsMath.h"

namespace XusoryEngine
{
	Matrix4x4 XsMath::BuildModelMatrix(const Vector3& position, const Vector3& scale)
	{
		const auto scaleMat = Matrix4x4::BuildScaleMatrix(scale.X(), scale.Y(), scale.Z());
		const auto translateMat = Matrix4x4::BuildTranslateMatrix(position.X(), position.Y(), position.Z());
		return scaleMat * translateMat;
	}

	Matrix4x4 XsMath::BuildViewMatrixLookUp(const Vector3& cameraPosition, const Vector3& targetPosition, const Vector3& worldUpDirection)
	{
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

	Matrix4x4 XsMath::BuildPerspectiveMatrixFov(FLOAT fovAngle, FLOAT aspect, FLOAT nearZ, FLOAT farZ)
	{
		return {
			1 / (aspect * std::tan(fovAngle / 2)), 0.0f, 0.0f, 0.0f,
			0.0f, 1 / std::tan(fovAngle / 2), 0.0f, 0.0f,
			0.0f, 0.0f, farZ / (farZ - nearZ), 1.0f,
			0.0f, 0.0f, -farZ * nearZ / (farZ - nearZ), 1.0f
		};
	}
}
