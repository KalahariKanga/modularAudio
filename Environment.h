#pragma once
#include "Synth.h"

class __declspec(dllexport) Environment
{
	std::vector<Synth*> synths;
	AudioBuffer buffer;
	
public:
	Environment();
	~Environment();

	Synth* addSynth();
	Synth* addSynth(std::string filename);
	short* getBuffer();
	void update();

};

