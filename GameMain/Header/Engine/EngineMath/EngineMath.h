#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	class Quaternion;
	class EngineMath
	{
	public:
		static Matrix4x4 BuildModelMatrix(const Float3& position, const Float3& scale);
		static Matrix4x4 BuildModelMatrix(const Vector3& position, const Vector3& scale, const Quaternion& quaternion);

		static Matrix4x4 BuildViewMatrixLookUp(const Float3& cameraPosition, const Float3& targetPosition, const Float3& worldUpDirection);
		static Matrix4x4 BuildViewMatrixLookUp(const Vector3& cameraPosition, const Vector3& targetPosition, const Vector3& worldUpDirection);

		static Matrix4x4 BuildPerspectiveMatrixFov(FLOAT fovAngle, FLOAT aspect, FLOAT nearZ, FLOAT farZ);

		static FLOAT Cycle(FLOAT num, FLOAT lowerBound, FLOAT upperBound);
	};
}
