#include "AudioComponent.h"

int AudioComponent::n;
AudioComponent::AudioComponent()
{
	startn = n;
}


AudioComponent::~AudioComponent()
{
}

void AudioComponent::render()
{
	buffer.zero();
	for (auto ac : ins)
		for (int c = 0; c < BUFFER_LENGTH; c++)
			buffer[c] += ac->buffer[c];
}

void AudioComponent::update()
{
	for (auto i : ins)
		i->update();
	render();
}

void AudioComponent::linkTo(AudioComponent* other)
{
	other->ins.push_back(this);
}