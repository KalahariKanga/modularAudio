#pragma once
#include "AudioComponent.h"
class AmpEnvelope :
	public AudioComponent
{
	float envelope(int c);
	float upTime;//time at which note is released
	short state;
public:
	AmpEnvelope();
	~AmpEnvelope();
	void render();
	
	void noteDown();
	void noteUp();
	Parameter a, d, s, r;
};

