#include "../EngineMath.h"
#include "../Quaternion.h"

namespace XusoryEngine
{
	Matrix4x4 EngineMath::BuildModelMatrix(const Float3& position, const Float3& scale)
	{
		const auto scaleMat = Matrix4x4::BuildScaleMatrix(scale.x, scale.y, scale.z);
		const auto translateMat = Matrix4x4::BuildTranslateMatrix(position.x, position.y, position.z);
		return scaleMat * translateMat;
	}

	Matrix4x4 EngineMath::BuildModelMatrix(const Vector3& position, const Vector3& scale, const Quaternion& quaternion)
	{
		const auto scaleMat = Matrix4x4::BuildScaleMatrix(scale.X(), scale.Y(), scale.Z());
		const auto rotateMat = Quaternion::BuildRotationMatrixByQuaternion(quaternion);
		const auto translateMat = Matrix4x4::BuildTranslateMatrix(position.X(), position.Y(), position.Z());
		return scaleMat * rotateMat * translateMat;
	}

	Matrix4x4 EngineMath::BuildViewMatrixLookUp(const Float3& cameraPosition, const Float3& targetPosition, const Float3& worldUpDirection)
	{
		const Vector3 cameraPositionVector = Vector3(cameraPosition);
		const Vector3 targetPositionVector = Vector3(targetPosition);
		const Vector3 worldUpDirectionVector = Vector3(worldUpDirection);

		const Vector3 forward = (targetPositionVector - cameraPositionVector).Normalize();
		const Vector3 right = Vector3::Cross(worldUpDirectionVector, forward).Normalize();
		const Vector3 upDirection = Vector3::Cross(forward, right);

		return {
			right.X(), upDirection.X(), forward.X(), 0.0f,
			right.Y(), upDirection.Y(), forward.Y(), 0.0f,
			right.Z(), upDirection.Z(), forward.Z(), 0.0f,
			-right.Dot(cameraPositionVector), -upDirection.Dot(cameraPositionVector), -forward.Dot(cameraPositionVector), 1.0f
		};
	}

	Matrix4x4 EngineMath::BuildViewMatrixLookUp(const Vector3& cameraPosition, const Vector3& targetPosition, const Vector3& worldUpDirection)
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

	Matrix4x4 EngineMath::BuildPerspectiveMatrixFov(FLOAT fovAngle, FLOAT aspect, FLOAT nearZ, FLOAT farZ)
	{
		return {
			1.0f / (aspect * std::tan(fovAngle / 2)), 0.0f, 0.0f, 0.0f,
			0.0f, 1 / std::tan(fovAngle / 2), 0.0f, 0.0f,
			0.0f, 0.0f, farZ / (farZ - nearZ), 1.0f,
			0.0f, 0.0f, -farZ * nearZ / (farZ - nearZ), 0.0f
		};
	}

	FLOAT EngineMath::Cycle(FLOAT num, FLOAT lowerBound, FLOAT upperBound)
	{
		if (num >= lowerBound && num <= upperBound)
		{
			return num;
		}

		const FLOAT range = upperBound - lowerBound;
		if (num > lowerBound)
		{
			while (num - lowerBound > range)
			{
				num -= range;
			}
		}
		else
		{
			while (upperBound - num > range)
			{
				num += range;
			}
		}

		return num;
	}
}
