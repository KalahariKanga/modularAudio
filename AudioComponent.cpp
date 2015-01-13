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
	for (auto l : links)
	{
		l.second->setValue(convertToRange(l.first->getValue(), l.first->min, l.first->max, l.second->min, l.second->max));
	}

	for (auto i : ins)
		i->update();

	render();
	needUpdate = 0;
}

void AudioComponent::outputTo(AudioComponent* other)
{
	other->ins.push_back(this);
}

