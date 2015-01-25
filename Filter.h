#pragma once
#include "AudioComponent.h"
class Filter :
	public AudioComponent
{
	float processSample(float in);
	float a0, a1, a2, b1, b2;
	float zx[2];
	float zy[2];
	void calcCoeffs();
	void render();
public:
	Filter();
	~Filter();
	Parameter type, freq, q;
};

