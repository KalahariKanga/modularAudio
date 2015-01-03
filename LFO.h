#pragma once
#include "AudioComponent.h"
class LFO :
	public AudioComponent
{
public:
	LFO();
	~LFO();
	Parameter value, freq;
	
	void render();
};

