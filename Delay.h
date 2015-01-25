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
public:
	Delay();
	Delay(float delayTime);
	~Delay();
	Parameter gain, feedback, dry, wet;
	void render();
};

