#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	DLL_STATIC_CLASS(GameTimer)
	{
		friend class GameManager;

	public:
		static FLOAT GetTime();
		static FLOAT GetDeltaTime();
		static DOUBLE GetTimeDouble();
		static DOUBLE GetDeltaTimeDouble();

	private:
		static BOOL sm_isInit;

		static DOUBLE sm_time;
		static DOUBLE sm_lastTime;

		static DOUBLE sm_lastRealTime;
	};
}
