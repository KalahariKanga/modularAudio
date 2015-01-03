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
		*(l.second) = *(l.first);

	for (auto i : ins)
		i->update();

	render();
}

void AudioComponent::outputTo(AudioComponent* other)
{
	other->ins.push_back(this);
}

float* AudioComponent::getParameter(std::string name)
{
	return parameters.at(name);
}

void AudioComponent::link(std::string name, AudioComponent* other, std::string othername)
{
	std::pair<float*, float*> l;
	l.first = getParameter(name);
	l.second = other->getParameter(othername);
	links.insert(l);
}