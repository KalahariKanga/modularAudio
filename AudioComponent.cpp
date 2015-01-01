#include "AudioComponent.h"


AudioComponent::AudioComponent()
{
	startn = n;
}


AudioComponent::~AudioComponent()
{
}

void AudioComponent::render()
{
	for (auto ac : ins)
		for (int c = 0; c < BUFFER_LENGTH; c++)
			buffer[c] += ac->buffer[c];
}