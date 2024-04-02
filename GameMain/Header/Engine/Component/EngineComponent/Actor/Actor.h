#pragma once

#include "../../Behaviour/Behaviour.h"

namespace XusoryEngine
{
	class Actor : public Behaviour
	{
	public:
		virtual void OnAwake();
		virtual void OnStart();
		virtual void OnDestroy();

		virtual void OnEnable();
		virtual void OnDisable();

		virtual void OnUpdate();
		virtual void OnLateUpdate();

	private:
		using Behaviour::Behaviour;
	};

#define XS_OBJECT	\
	XS_CLASS;		\
	using Actor::Actor
}
