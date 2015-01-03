#pragma once
#include "Oscillator.h"
class AdditiveOscillator :
	public Oscillator
{
public:
	AdditiveOscillator();
	~AdditiveOscillator();
	double getSample(double pos);
	Parameter amount[64];
};

