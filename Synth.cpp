#include "Synth.h"


Synth::Synth()
{
	for (int c = 0; c < polyphony; c++)
	{
		collections.push_back(new Collection);
		//something something delete...
	}
}


Synth::~Synth()
{
}

void Synth::update()
{
	activeNotes = 0;
	for (auto c : collections)
	{
		c->update();
		if (!c->isIdle())
			activeNotes++;
	}
	buffer.zero();
	for (auto c : collections)
		for (int t = 0; t < BUFFER_LENGTH; t++)
			buffer.data[t] += ((AudioComponent*)(c->outputComponent))->buffer.data[t];
	
}

void Synth::addComponent(std::string name, std::string type)
{
	for (auto c : collections)
		c->addComponent(name, type);
}

void Synth::setParameter(std::string component, std::string parameter, float value)
{
	for (auto c : collections)
	{
		c->setParameter(component, parameter, value);
	}
}

void Synth::linkAudio(std::string from, std::string to)
{
	for (auto c : collections)
		c->linkAudio(from, to);
}

void Synth::linkCV(std::string from, std::string param1, std::string to, std::string param2)
{
	for (auto c : collections)
		c->linkCV(from, param1, to, param2);
}

void Synth::noteDown(Note note)
{
	for (auto c : collections)
		if (c->note.note == note.note)
			return;
	for (auto c : collections)
		if (c->isIdle())
		{
			c->note = note;
			c->noteDown();
			return;
		}
	//if all components are active
}

void Synth::noteUp(Note note)
{
	for (auto c : collections)
		if (c->note.note == note.note)
			c->noteUp();
}