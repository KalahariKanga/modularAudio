#include "SimpleOscillator.h"


SimpleOscillator::SimpleOscillator()
{
	addParameter(&waveform, "waveform", 0, 0, 3);
	addParameter(&pulseWidth, "pulseWidth", 0.5, 0, 1);
}


SimpleOscillator::~SimpleOscillator()
{
}

double SimpleOscillator::getSample(double pos)
{
	switch ((int)(waveform.getValue()))
	{
	case 0:
		return sin(pos);
		break;
	case 1:
		return square(pos, pulseWidth.getValue()); //could this be slow?
		break;
	case 2:
		return triangle(pos,0);
		break;
	case 3:
		return triangle(pos, pulseWidth.getValue());
		break;
	}
	return 0;
}

float SimpleOscillator::square(float t, float pw)
{
	t = fmod((double)t, (double)2 * PI);
	return (t < pw * 2 * PI) ? -1 : 1;
}

float SimpleOscillator::triangle(float t, float pw)
{
	if (pw == 0)
		pw = 1;
	t = fmod((double)t, (double)2 * PI);
	if (t < pw * 2 * PI)
		return (t / (pw*PI)) - 1;
	else
		return 1 + (-t + pw * 2 * PI) / ((1 - pw)*PI);
}