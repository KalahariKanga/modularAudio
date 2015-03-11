#include "Environment.h"


Environment::Environment()
{
}


Environment::~Environment()
{
}

Synth* Environment::addSynth()
{
	synths.push_back(new Synth());
	return synths.back();
}

Synth* Environment::addSynth(std::string filename)
{
	synths.push_back(new Synth());
	synths.back()->loadPatch(filename);
	return synths.back();
}

short* Environment::getBuffer()
{
	return buffer.data;
}

void Environment::update()
{
	buffer.zero();
	for (auto s : synths)
		s->update();
	for (auto s : synths)
	{
		for (int c = 0; c < BUFFER_LENGTH; c++)
			buffer[c] += s->getBuffer()[c];
	}
	AudioComponent::n++;
}