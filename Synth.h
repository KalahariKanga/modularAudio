#pragma once
#include "Collection.h"
#include "AudioBuffer.h"

class __declspec(dllexport) Synth
{
	std::vector<Collection*> collections;
	const int polyphony = 16;
	AudioBuffer buffer;
	float noteUpTimer[100];
	int activeNotes;
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
	
	short* getBuffer();
	Component* getComponent(std::string name);
	void savePatch(std::string fname);
	void loadPatch(std::string fname);
	void playNoteDuration(Note note, float seconds);

	std::vector<std::string> getComponentList();


};

