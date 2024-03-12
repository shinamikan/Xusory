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

		template <typename T>
		auto Invoke(const std::string_view& funcName, FLOAT delayTime);
		template <typename T>
		void InvokeRepeating(const std::string_view& funcName, INT repeatCount, FLOAT firstDelayTime, FLOAT repeatDelayTime);
		void CancelAllInvoke();
		BOOL HasInvoke();

	protected:

	private:
		using Behaviour::Behaviour;
	};
}
