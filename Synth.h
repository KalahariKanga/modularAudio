#pragma once
#include "Collection.h"
#include "AudioBuffer.h"

class __declspec(dllexport) Synth
{
	std::vector<Collection*> collections;
	const int polyphony = 16;
	AudioBuffer buffer;
public:
	Synth();
	~Synth();
	
	void update();
	void addComponent(std::string name, std::string type);
	void setParameter(std::string component, std::string parameter, float value);
	void setParameterRaw(std::string component, std::string parameter, float value);
	void linkAudio(std::string from, std::string to);
	void linkCV(std::string from, std::string param1, std::string to, std::string param2, float amount);
	void noteDown(Note note);
	void noteUp(Note note);
	int activeNotes;
	short* getBuffer();
	void savePatch(std::string fname);
	void loadPatch(std::string fname);
	
};

