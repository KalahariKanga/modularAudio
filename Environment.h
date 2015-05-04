#pragma once
#include "Synth.h"
#include "MidiPlayer.h"

class __declspec(dllexport) Environment
{
	std::vector<Synth*> synths;
	AudioBuffer buffer;
	

	std::chrono::time_point<std::chrono::system_clock> start, end;
	
	
public:
	Environment();
	~Environment();

	std::vector<MidiEvent> events;
	std::vector<MidiPlayer*> players;
	Synth* addSynth();
	Synth* addSynth(std::string filename);
	short* getBuffer();
	MidiPlayer* addPlayer(std::string filename);
	void update();
};

