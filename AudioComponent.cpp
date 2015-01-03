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
		l.second->value = convertToRange(l.first->value, l.first->min, l.first->max, l.second->min, l.second->max);
	}

	for (auto i : ins)
		i->update();

	render();
}

void AudioComponent::outputTo(AudioComponent* other)
{
	other->ins.push_back(this);
}

Parameter* AudioComponent::getParameter(std::string name)
{
	return parameters.at(name);
}

void AudioComponent::link(std::string name, AudioComponent* other, std::string othername)
{
	std::pair<Parameter*, Parameter*> l;
	l.first = getParameter(name);
	l.second = other->getParameter(othername);
	links.push_back(l);
}