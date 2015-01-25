#include "ComponentFactory.h"


ComponentFactory::ComponentFactory()
{
}


ComponentFactory::~ComponentFactory()
{
}

Component* ComponentFactory::makeComponent(std::string type)
{
	/*not quite a factory method, check 
	http://www.codeproject.com/Articles/567242/AplusC-b-bplusObjectplusFactory
	*/
	if (type == "AdditiveOscillator")
		return new AdditiveOscillator();
	if (type == "AmpEnvelope")
		return new AmpEnvelope();
	if (type == "LFO")
		return new LFO();
	if (type == "AudioOutput")
		return new AudioOutput();
	if (type == "SimpleOscillator")
		return new SimpleOscillator();
	if (type == "Delay")
		return new Delay();
	if (type == "Filter")
		return new Filter();
	return nullptr;
}