#pragma once

#include "../../Behaviour/Behaviour.h"

namespace XusoryEngine
{
	class MeshRenderer : public Behaviour
	{
		XS_CLASS;

		EXPOSED_CONST_FUNCTION(MeshRenderer, public, Material*, GetMaterial);
		EXPOSED_FUNCTION(MeshRenderer, public, void, SetMaterial, const Material* material);

		EXPOSED_VARIABLE_VALUE(public, BOOL, isVisible, true);
		EXPOSED_VARIABLE_VALUE(public, UINT, renderingLayer, 0);

		EXPOSED_VARIABLE_VALUE(public, Mesh*, mesh, nullptr);

	private:
		using Behaviour::Behaviour;

		Material* m_material = nullptr;
	};
}
