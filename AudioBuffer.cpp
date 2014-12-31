#include "AudioBuffer.h"


AudioBuffer::AudioBuffer()
{
	data = new short[BUFFER_LENGTH];
	for (int c = 0; c < BUFFER_LENGTH; c++)
		data[c] = 0;
}


AudioBuffer::~AudioBuffer()
{
	delete data;
}

short& AudioBuffer::operator[](int i)
{
	if (i < 0)
		return data[0];
	if (i >= BUFFER_LENGTH)
		return data[BUFFER_LENGTH - 1];
	return data[i];
}