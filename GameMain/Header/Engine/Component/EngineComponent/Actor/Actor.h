#pragma once

#include "../../Behaviour/Behaviour.h"

namespace XusoryEngine
{
	class Actor : public Behaviour
	{
	public:
		static void Invoke();
		static void InvokeRepeating();
		static void CancelAllInvoke();
		static BOOL HasInvoke();

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
}
