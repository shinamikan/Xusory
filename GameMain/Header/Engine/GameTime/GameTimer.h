#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	class GameTimer
	{
	public:
		static FLOAT GetTime();
		static FLOAT GetDeltaTime();
		static DOUBLE GetTimeDouble();
		static DOUBLE GetDeltaTimeDouble();
		
		static FLOAT GetFixedTime();
		static FLOAT GetFixedDeltaTime();
		static DOUBLE GetFixedTimeDouble();
		static DOUBLE GetFixedDeltaTimeDouble();

		static FLOAT GetRealTime();
		static FLOAT GetDeltaRealTime();
		static DOUBLE GetRealTimeDouble();
		static DOUBLE GetDeltaRealTimeDouble();

		static FLOAT fixedTimeStep;
		static FLOAT maximumDeltaTime;

	private:
		static DOUBLE sm_time;
		static DOUBLE sm_lastTime;

		static DOUBLE sm_fixedTime;
		static DOUBLE sm_lastFixedTime;

		static DOUBLE sm_lastRealTime;
	};
}
