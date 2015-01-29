#pragma once
#include "AudioComponent.h"
class Delay :
	public AudioComponent
{
	std::vector<float> myBuffer;
	int bufferLength, pos;
	float get();
	void set(float v);
	float processSample(float d, float w);
	AudioBuffer temp;
	float previousLength;
public:
	Delay();
	~Delay();
	Parameter gain, feedback, dry, wet, length;
	void render();
};

