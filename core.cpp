#include "core.h"

float clamp(float value, float min, float max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

float convertToRange(float value, float oldmin, float oldmax, float newmin, float newmax)
{
	float frac = (value - oldmin) / (oldmax - oldmin);
	return newmin + frac * (newmax - newmin);
}