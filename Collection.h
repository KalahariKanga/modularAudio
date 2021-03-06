#pragma once
#include "core.h"
#include "SimpleOscillator.h"
#include "AmpEnvelope.h"
#include "AdditiveOscillator.h"
#include "AudioOutput.h"
#include "LFO.h"
#include "ComponentFactory.h"

class Collection
{
	bool idle;
public:
	
	Collection();
	~Collection();
	std::map<std::string, Component*> components;
	std::vector<Link> links;
	Component* outputComponent;
	void update();
	void addComponent(std::string name, std::string type);
	void setParameter(std::string component, std::string parameter, float value);
	void setParameterRaw(std::string component, std::string parameter, float value);
	void linkAudio(std::string from, std::string to);
	void linkCV(std::string from, std::string param1, std::string to, std::string param2, float amount);
	void noteDown();
	void noteUp();
	bool isIdle();
	void setIdle(bool i);
	Note note;
	int noteState; //0 up 1 down
};

