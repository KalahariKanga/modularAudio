#include "AudioComponent.h"
#include <climits>

int AudioComponent::n;
AudioComponent::AudioComponent()
{
	startn = n;
	output.create(0, SHRT_MIN, SHRT_MAX, 1);
	gain.create(0, -1, 1);
	parameters.insert(std::pair<std::string, Parameter*>("output", &output));
	parameters.insert(std::pair<std::string, Parameter*>("gain", &gain));
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
	float v = (buffer[0] + buffer[BUFFER_LENGTH / 3] + buffer[2 * BUFFER_LENGTH / 3]) / 3;
	output.setBaseValue(v);

	/*this could be incorporated into a component::getSample(int c) function*/
	for (int c = 0; c < BUFFER_LENGTH; c++)
		buffer.data[c] += buffer.data[c] * gain.getValue();

	needUpdate = 0;
}

void AudioComponent::outputTo(AudioComponent* other)
{
	other->ins.push_back(this);
}

