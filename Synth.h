#pragma once
#include "Collection.h"
class Synth
{
public:
	Synth();
	~Synth();
	std::vector<Collection*> collections;
	const int polyphony = 16;
	AudioBuffer buffer;
	void update();
	void addComponent(std::string name, std::string type);
	void setParameter(std::string component, std::string parameter, float value);
	void linkAudio(std::string from, std::string to);
	void linkCV(std::string from, std::string param1, std::string to, std::string param2);
	void noteDown(Note note);
	void noteUp(Note note);
	int activeNotes;
};

