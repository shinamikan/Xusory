#pragma once

#include "../../Behaviour/Behaviour.h"

namespace XusoryEngine
{
	class MeshRenderer : public Behaviour
	{
		XS_CLASS;

		EXPOSED_VARIABLE_VALUE(public, BOOL, isVisible, true);
		EXPOSED_VARIABLE_VALUE(public, UINT, renderingLayer, 0);

		EXPOSED_VARIABLE_VALUE(public, Material*, material, nullptr);
		EXPOSED_VARIABLE_VALUE(public, Mesh*, mesh, nullptr);
		//EXPOSED_VARIABLE(public, std::vector<Material*>, materials);

	private:
		using Behaviour::Behaviour;
	};
}
