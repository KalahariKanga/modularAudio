#include "Environment.h"
#include <chrono>
#include <thread>
#include "SFML/graphics.hpp"
#include "bass.h"

sf::Texture tex;
sf::Image image;
sf::Sprite sprite;
sf::RenderWindow window;
void update(Synth* s);
int sfkeyToNote(sf::Keyboard::Key);


int main(int argc, char** argv[])
{
	window.create(sf::VideoMode(512, 64), "modularAudio");
	window.setKeyRepeatEnabled(0);
	image.create(512, 64);

	BASS_Init(-1, SAMPLE_RATE, 0, 0, NULL);
	BASS_SetConfig(BASS_CONFIG_BUFFER, 128);
	BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 10);
	HSTREAM stream = BASS_StreamCreate(SAMPLE_RATE, 1, 0, STREAMPROC_PUSH, NULL);
	BASS_ChannelPlay(stream, 0);

	srand(time(0));

	Environment e;
	Synth* s = e.addSynth();
	s->addComponent("osc", "SimpleOscillator");
	s->addComponent("env", "AmpEnvelope");
	s->linkAudio("osc", "env");
	s->linkAudio("env", "output");
	s->setParameterRaw("output", "gain",1.7);
	s->setParameterRaw("osc", "octaves", 1);
	
	Synth* s1 = e.addSynth();
	s1->addComponent("osc", "SimpleOscillator");
	s1->addComponent("env", "AmpEnvelope");
	s1->linkAudio("osc", "env");
	s1->linkAudio("env", "output");
	s1->setParameterRaw("osc", "waveform", 1);

	Synth* s2 = e.addSynth();
	s2->addComponent("osc", "SimpleOscillator");
	s2->addComponent("env", "AmpEnvelope");
	s2->linkAudio("osc", "env");
	s2->linkAudio("env", "output");
	s2->setParameterRaw("osc", "waveform", 1);
	
	short* output = e.getBuffer();
	std::chrono::time_point<std::chrono::system_clock> start, end;
	AudioComponent::n = 0;
	//s->playNoteDuration(Note(c3, 100), 3);
	MidiPlayer* mp = e.addPlayer("tithe.mid");
	mp->assignTrack(0, s);
	mp->assignTrack(1, s1);
	mp->assignTrack(2, s);
	mp->assignTrack(3, s2);
	mp->play();

	while (1)
	{
		
		start = std::chrono::system_clock::now();
		e.update();
		update(s);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		//std::cout << elapsed_seconds.count() << std::endl;

		

		while (BASS_StreamPutData(stream, NULL, 0) > 10);
		BASS_StreamPutData(stream, (void*)output, BUFFER_LENGTH*sizeof(short));
		
	}

	BASS_StreamFree(stream);
	BASS_Stop();
	BASS_Free();
}

void update(Synth* s)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			Note n((Notes)sfkeyToNote(event.key.code), 1);
			if (n.note != NONOTE)
				s->noteDown(n);
		}
		if (event.type == sf::Event::KeyReleased)
		{
			Note n((Notes)sfkeyToNote(event.key.code), 1);
			if (n.note != NONOTE)
				s->noteUp(n);
		}
	}
	//clear screen
	for (int cx = 0; cx < 512; cx++)
		for (int cy = 0; cy<64; cy++)
			image.setPixel(cx, cy, sf::Color(0, 0, 0));

	//draw waveform
	for (int c = 0; c < BUFFER_LENGTH; c++)
		if (abs((s->getBuffer())[c] / 16) < 32)
			image.setPixel(((float)c / BUFFER_LENGTH) * 512, 32 + (s->getBuffer())[c] / 16, sf::Color(255, 255, 255));

	tex.loadFromImage(image);
	sprite.setTexture(tex);
	window.draw(sprite);
	window.display();
}

int sfkeyToNote(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::A:
		return c3;
		break;
	case sf::Keyboard::W:
		return cs3;
		break;
	case sf::Keyboard::S:
		return d3;
		break;
	case sf::Keyboard::E:
		return ds3;
		break;
	case sf::Keyboard::D:
		return e3;
		break;
	case sf::Keyboard::F:
		return f3;
		break;
	case sf::Keyboard::T:
		return fs3;
		break;
	case sf::Keyboard::G:
		return g3;
		break;
	case sf::Keyboard::Y:
		return gs3;
		break;
	case sf::Keyboard::H:
		return a3;
		break;
	case sf::Keyboard::U:
		return as3;
		break;
	case sf::Keyboard::J:
		return b3;
		break;
	case sf::Keyboard::K:
		return c4;
		break;
	default:
		return NONOTE;
	}
}