#pragma once

#include "../../Behaviour/Behaviour.h"

namespace XusoryEngine
{
	enum class LightType
	{
		DIRECTIONAL = 0,
		POINT
	};

	DLL_CLASS(Light) : public Behaviour
	{
		XS_CLASS;

	public:
		EXPOSED_CONST_FUNCTION(Light, public, Vector3, GetLightWorldPosition);
		EXPOSED_CONST_FUNCTION(Light, public, Vector3, GetLightWorldDirection);

		EXPOSED_VARIABLE_VALUE(public, LightType, lightType, LightType::DIRECTIONAL);
		EXPOSED_VARIABLE_VALUE(public, Vector3, color, Vector3(1.0f, 1.0f, 1.0f));
		EXPOSED_VARIABLE_VALUE(public, FLOAT, intensity, 1.0f);
		EXPOSED_VARIABLE_VALUE(public, FLOAT, range, 10.0f);

		static Vector3 ambient;

	private:
		using Behaviour::Behaviour;
	};
}
