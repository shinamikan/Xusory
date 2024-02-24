#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	class XsMath
	{
	public:
		static Matrix4x4 BuildModelMatrix(const Vector3& position, const Vector3& scale);
		static Matrix4x4 BuildViewMatrixLookUp(const Vector3& cameraPosition, const Vector3& targetPosition, const Vector3& worldUpDirection);
		static Matrix4x4 BuildPerspectiveMatrixFov(FLOAT fovAngle, FLOAT aspect, FLOAT nearZ, FLOAT farZ);
	};
}
