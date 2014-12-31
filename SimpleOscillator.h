#pragma once
#include "AudioComponent.h"
class SimpleOscillator :
	public AudioComponent
{
public:
	SimpleOscillator();
	~SimpleOscillator();
	void render();
};

