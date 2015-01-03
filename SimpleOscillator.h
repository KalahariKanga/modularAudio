#pragma once
#include "AudioComponent.h"
#include "Oscillator.h"
class SimpleOscillator :
	public Oscillator
{
public:
	SimpleOscillator();
	~SimpleOscillator();
	double getSample(double pos);
};

