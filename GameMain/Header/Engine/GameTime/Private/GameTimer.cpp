#include "../GameTimer.h"

namespace XusoryEngine
{
	FLOAT GameTimer::fixedTimeStep = 0.02f;
	FLOAT GameTimer::maximumDeltaTime = 0.3f;

	DOUBLE GameTimer::sm_time = 0.0f;
	DOUBLE GameTimer::sm_lastTime = 0.0f;
	DOUBLE GameTimer::sm_fixedTime = 0.0f;
	DOUBLE GameTimer::sm_lastFixedTime = 0.0f;
	DOUBLE GameTimer::sm_lastRealTime = 0.0f;

	FLOAT GameTimer::GetTime()
	{
		return static_cast<FLOAT>(sm_time);
	}

	FLOAT GameTimer::GetDeltaTime()
	{
		return static_cast<FLOAT>(sm_time - sm_lastTime);
	}

	DOUBLE GameTimer::GetTimeDouble()
	{
		return sm_time;
	}

	DOUBLE GameTimer::GetDeltaTimeDouble()
	{
		return sm_time - sm_lastTime;
	}

	FLOAT GameTimer::GetFixedTime()
	{
		return static_cast<FLOAT>(sm_fixedTime);
	}

	FLOAT GameTimer::GetFixedDeltaTime()
	{
		return static_cast<FLOAT>(sm_fixedTime - sm_lastFixedTime);
	}

	DOUBLE GameTimer::GetFixedTimeDouble()
	{
		return sm_fixedTime;
	}

	DOUBLE GameTimer::GetFixedDeltaTimeDouble()
	{
		return sm_fixedTime - sm_lastFixedTime;
	}

	FLOAT GameTimer::GetRealTime()
	{
		return static_cast<FLOAT>(PerformanceTime::GetTime());
	}

	DOUBLE GameTimer::GetRealTimeDouble()
	{
		return PerformanceTime::GetTime();
	}

	FLOAT GameTimer::GetDeltaRealTime()
	{
		return static_cast<FLOAT>(PerformanceTime::GetTime() - sm_lastRealTime);
	}

	DOUBLE GameTimer::GetDeltaRealTimeDouble()
	{
		return PerformanceTime::GetTime() - sm_lastRealTime;
	}
}
