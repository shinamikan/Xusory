#pragma once

#include "../../Behaviour/Behaviour.h"

namespace XusoryEngine
{
	enum class ViewMode
	{
		LOOKUP = 0,
		TRANSFORM
	};

	class Camera : public Behaviour
	{
		XS_CLASS;

	public:
		EXPOSED_CONST_FUNCTION(Camera, public, Matrix4x4, GetViewMatrix);
		EXPOSED_CONST_FUNCTION(Camera, public, Matrix4x4, GetProjectionMatrix);

		EXPOSED_VARIABLE_VALUE(public, ViewMode, viewMode, ViewMode::LOOKUP);
		EXPOSED_VARIABLE_VALUE(public, FLOAT, fieldOfView, 45.0f);
		EXPOSED_VARIABLE_VALUE(public, FLOAT, nearPlane, 1.0f);
		EXPOSED_VARIABLE_VALUE(public, FLOAT, farPlane, 1000.0f);
		EXPOSED_VARIABLE_VALUE(public, Vector3, targetPosition, Vector3(0.0f, 0.0f, 0.0f));

		FLOAT aspect;

		static Camera* mainCamera;

	private:
		using Behaviour::Behaviour;
	};
}
