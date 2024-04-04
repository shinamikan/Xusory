#include "../GameTimer.h"

namespace XusoryEngine
{
	BOOL GameTimer::sm_isInit = false;

	DOUBLE GameTimer::sm_time = 0.0;
	DOUBLE GameTimer::sm_lastTime = 0.0;
	DOUBLE GameTimer::sm_lastRealTime = 0.0;

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
}
