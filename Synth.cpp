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
	for (auto c : collections)
		c->update();
}

void Synth::addComponent(std::string name, std::string type)
{
	for (auto c : collections)
		c->addComponent(name, type);
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
		}
	//if all components are active
}

void Synth::noteUp(Note note)
{
	for (auto c : collections)
		if (c->note.note == note.note)
			c->noteUp();
}