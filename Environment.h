#pragma once
#include "Synth.h"
#include "MidiFile.h"

class __declspec(dllexport) Environment
{
	std::vector<Synth*> synths;
	AudioBuffer buffer;
	MidiFile midifile;
	bool midiFileIsPlaying = 0;
	int midiEventCount[16] = {};
	float midiTicks = 0;
	int tickLength;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::map<int, Synth*> synthMap;
public:
	Environment();
	~Environment();

	Synth* addSynth();
	Synth* addSynth(std::string filename);
	short* getBuffer();
	void update();
	void loadMidiFile(std::string fname);
	void assignMidiTrack(int track, Synth* s);
	void playMidiFile();
};

