#pragma once
#include "AudioComponent.h"
class LFO :
	public AudioComponent
{
public:
	LFO();
	~LFO();
	float value;
	float freq;
	void render();
};

