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
		Matrix4x4 GetViewMatrix() const;

		EXPOSED_VARIABLE_VALUE(public, ViewMode, viewMode, ViewMode::LOOKUP);
		EXPOSED_VARIABLE_VALUE(public, Vector3, targetPosition, Vector3(0.0f, 0.0f, 0.0f));

	private:
		using Behaviour::Behaviour;
	};
}
