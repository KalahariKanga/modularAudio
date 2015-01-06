#pragma once
#include "SimpleOscillator.h"
#include "AmpEnvelope.h"
#include "AdditiveOscillator.h"
#include "AudioOutput.h"
#include "LFO.h"

class ComponentFactory
{
public:
	ComponentFactory();
	~ComponentFactory();
	static Component* makeComponent(std::string type);
};

