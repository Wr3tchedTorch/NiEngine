#pragma once

namespace ni {

struct MathUtility
{
	template <typename T>
	static int GetSign(T number)
	{
		return (number > 0) - (number < 0);
	}
};

}