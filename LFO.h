#pragma once
#include "AudioComponent.h"
class LFO :
	public Component
{
public:
	LFO();
	~LFO();
	Parameter value, freq;
	
	void render();
};

