#pragma once

#include "../Component.h"

namespace XusoryEngine
{
	DLL_CLASS(Behaviour) : public Component
	{
	public:
		void SetEnable(BOOL newEnable);
		BOOL enable = true;

	protected:
		using Component::Component;
	};
}
