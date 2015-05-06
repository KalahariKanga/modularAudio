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

MidiPlayer* Environment::addPlayer(std::string fname)
{
	MidiPlayer* mp = new MidiPlayer(fname);
	players.push_back(mp);
	mp->ID = players.size();
	return mp;
}

void Environment::update()
{
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	//play midi file
	for (auto c : players)
		c->update(0); //put in delta
	start = std::chrono::system_clock::now();
	




	buffer.zero();
	//update synths
	for (auto s : synths)
		s->update();
	//collate buffers
	for (auto s : synths)
	{
		for (int c = 0; c < BUFFER_LENGTH; c++)
			buffer[c] += s->getBuffer()[c];
	}
	
	AudioComponent::n++;
}
