#pragma once
#include "AudioComponent.h"
class Oscillator :
	public AudioComponent
{
	int phase;
public:
	Oscillator();
	~Oscillator();
	void render();
	virtual double getSample(double pos) = 0;
	Parameter octaves, semitones;
};

