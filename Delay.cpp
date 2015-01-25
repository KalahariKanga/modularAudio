#include "Delay.h"

Delay::Delay() : Delay(0.3)
{}
Delay::Delay(float delayTime)
{
	//gain.create()
	feedback.create(0.4, 0, 1);
	dry.create(0.8, 0, 1);
	wet.create(0.5, 0, 1);
	parameters.insert(std::pair<std::string, Parameter*>("feedback", &feedback));
	parameters.insert(std::pair<std::string, Parameter*>("dry", &dry));
	parameters.insert(std::pair<std::string, Parameter*>("wet", &wet));
	
	bufferLength = delayTime * SAMPLE_RATE;
	myBuffer = new float[bufferLength];
	for (int c = 0; c < bufferLength; c++)
		myBuffer[c] = 0;
}


Delay::~Delay()
{
	delete[] myBuffer;
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
}