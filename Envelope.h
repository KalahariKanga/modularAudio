#pragma once
#include "Component.h"
class Envelope :
	public Component
{
	float upTime;
	short state;
	float releaseValue, v = 0;
public:
	Envelope();
	~Envelope();

	void update();
	void noteDown();
	void noteUp();
	Parameter a, d, s, r, value;
};

