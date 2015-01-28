#include "Synth.h"


Synth::Synth()
{
	for (int c = 0; c < polyphony; c++)
	{
		collections.push_back(new Collection);
		//something something delete...
	}
	window.create(sf::VideoMode(512, 64), "modularAudio");
	window.setKeyRepeatEnabled(0);
	
	image.create(512, 64);
}


Synth::~Synth()
{
}

void Synth::update()
{
	handleInput();
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

	//clear screen
	for (int cx = 0; cx < 512; cx++)
		for (int cy = 0; cy<64; cy++)
			image.setPixel(cx, cy, sf::Color(0, 0, 0));

	//draw waveform
	for (int c = 0; c < BUFFER_LENGTH; c++)
		if (abs(buffer[c] / 16) < 32)
			image.setPixel(((float)c / BUFFER_LENGTH) * 512, 32 + buffer[c] / 16, sf::Color(255, 255, 255));

	tex.loadFromImage(image);
	sprite.setTexture(tex);
	window.draw(sprite);
	window.display();
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

void Synth::setParameterRaw(std::string component, std::string parameter, float value)
{
	for (auto c : collections)
	{
		c->setParameterRaw(component, parameter, value);
	}
}

void Synth::linkAudio(std::string from, std::string to)
{
	for (auto c : collections)
		c->linkAudio(from, to);
}

void Synth::linkCV(std::string from, std::string param1, std::string to, std::string param2, float amount)
{
	for (auto c : collections)
		c->linkCV(from, param1, to, param2, amount);
}

void Synth::noteDown(Note note)
{
	for (auto c : collections)
		if (c->note.note == note.note && c->noteState == 1)
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

void Synth::handleInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			noteDown(Note(event.key.code, 100));
		}
		if (event.type == sf::Event::KeyReleased)
		{
			noteUp(Note(event.key.code,100));
		}
	}

}