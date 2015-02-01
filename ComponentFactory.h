#pragma once
#include "SimpleOscillator.h"
#include "AmpEnvelope.h"
#include "AdditiveOscillator.h"
#include "AudioOutput.h"
#include "LFO.h"
#include "Delay.h"
#include "Filter.h"
#include "NoiseOscillator.h"
#include "Envelope.h"

class ComponentFactory
{
public:
	ComponentFactory();
	~ComponentFactory();
	static Component* makeComponent(std::string type);
};

