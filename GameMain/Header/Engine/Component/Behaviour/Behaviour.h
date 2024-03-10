#pragma once

#include "../Component.h"

namespace XusoryEngine
{
	class Behaviour : public Component
	{
	public:
		void SetEnable(BOOL newEnable);
		BOOL enable = true;

	protected:
		using Component::Component;
	};
}
