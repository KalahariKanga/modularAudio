#pragma once
#include "AudioComponent.h"
class AmpEnvelope :
	public AudioComponent
{
	float envelope(int c);
public:
	AmpEnvelope();
	~AmpEnvelope();
	void render();
	
	void noteDown();
};

