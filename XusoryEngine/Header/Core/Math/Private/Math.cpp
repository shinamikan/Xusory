#include "../Math.h"

namespace XusoryEngine
{
	FLOAT Math::Cycle(FLOAT num, FLOAT lowerBound, FLOAT upperBound)
	{
		if (num >= lowerBound && num <= upperBound)
		{
			return num;
		}

		const FLOAT range = upperBound - lowerBound;
		if (num > lowerBound)
		{
			while (num - lowerBound > range)
			{
				num -= range;
			}
		}
		else
		{
			while (upperBound - num > range)
			{
				num += range;
			}
		}

		return num;
	}

	FLOAT Math::DegreeToRadian(FLOAT degree)
	{
		return degree * Pi / 180.0f;
	}

	FLOAT Math::RadianToDegree(FLOAT radian)
	{
		return radian * 180.0f / Pi;
	}
}
