#include "Delay.h"

Delay::Delay()
{
	
	addParameter(&feedback, "feedback", 0.4, 0, 1);
	addParameter(&dry, "dry", 0.8, 0, 1);
	addParameter(&wet, "wet", 0.5, 0, 1);
	addParameter(&length, "length", 0.3, 0, 2);
	bufferLength = length.getValue() * SAMPLE_RATE;
	myBuffer.insert(myBuffer.begin(), bufferLength, 0);
}


Delay::~Delay()
{

}

float Delay::get()
{
	return myBuffer[pos];
}

void Delay::set(float v)
{
	myBuffer[pos] = v + myBuffer[pos] * feedback.getValue();
	pos++;
	if (pos == bufferLength)
		pos = 0;
}

float Delay::processSample(float d, float w)
{
	return d * dry.getValue() + w * wet.getValue();
}

void Delay::render()
{
	float delaySample, in, out;
	temp.zero();
	for (auto i : ins)
	{
		for (int c = 0; c < BUFFER_LENGTH; c++)
			temp[c] += i->buffer[c];
	}
	for (int c = 0; c < BUFFER_LENGTH; c++)
	{
		delaySample = get();
		set(temp[c]);
		buffer.data[c] = processSample(temp[c], delaySample);
	}
	if (previousLength != length.getValue())
	{
		bufferLength = length.getValue() * SAMPLE_RATE;
		myBuffer.resize(bufferLength);
		if (pos >= bufferLength)
			pos = 0;
	}
	previousLength = length.getValue();
}