#pragma once
#include "MidiFile.h"
#include "MidiPlayerEvent.h"
#include "Synth.h"
class _declspec(dllexport) MidiPlayer
{
	bool isPlaying;
	int midiTicks;
	MidiFile midifile;
	int midiEventCount[16] = {};
	std::map<int, Synth*> synthMap;
	float tickLength;
public:
	MidiPlayer(std::string);
	~MidiPlayer();

	std::vector<MidiPlayerEvent> events;

	void update(float delta);
	void loadFile(std::string);
	void assignTrack(int track, Synth* s);
	void play();
	void setTicks(int ticks);
	int ID;
};

