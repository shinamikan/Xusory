#pragma once

#include "../../Behaviour/Behaviour.h"

namespace XusoryEngine
{
	DLL_CLASS(Camera) : public Behaviour
	{
		friend class GameManager;
		XS_CLASS;

	public:
		EXPOSED_CONST_FUNCTION(Camera, public, FLOAT, GetAspect);
		EXPOSED_CONST_FUNCTION(Camera, public, Matrix4x4, GetViewMatrix);
		EXPOSED_CONST_FUNCTION(Camera, public, Matrix4x4, GetProjectionMatrix);

		EXPOSED_VARIABLE_VALUE(public, FLOAT, fieldOfView, 45.0f);
		EXPOSED_VARIABLE_VALUE(public, FLOAT, nearPlane, 1.0f);
		EXPOSED_VARIABLE_VALUE(public, FLOAT, farPlane, 1000.0f);

		static Camera* mainCamera;

	private:
		using Behaviour::Behaviour;
		FLOAT aspect = 0.0f;
	};
}
