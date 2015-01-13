#pragma once
#include "AudioComponent.h"
#include "Oscillator.h"

class SimpleOscillator :
	public Oscillator
{
	float square(float t, float pw);
	float triangle(float t, float pw);
public:
	SimpleOscillator();
	~SimpleOscillator();
	double getSample(double pos);
	Parameter waveform;
	Parameter pulseWidth;
};

