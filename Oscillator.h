#pragma once
#include "AudioComponent.h"
class Oscillator :
	public AudioComponent
{
public:
	Oscillator();
	~Oscillator();
	void render();
	virtual double getSample(double pos) = 0;
};

