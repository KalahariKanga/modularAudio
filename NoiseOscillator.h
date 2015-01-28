#pragma once
#include "Oscillator.h"
class NoiseOscillator :
	public Oscillator
{
public:
	NoiseOscillator();
	~NoiseOscillator();
	double getSample(double pos);
	Parameter type;
};

