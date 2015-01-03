#pragma once
#include "Oscillator.h"
class AdditiveOscillator :
	public Oscillator
{
public:
	AdditiveOscillator();
	~AdditiveOscillator();
	double getSample(double pos);
	float amount[64];
};

