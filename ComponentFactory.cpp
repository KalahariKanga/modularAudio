#include "ComponentFactory.h"


ComponentFactory::ComponentFactory()
{
	
}


ComponentFactory::~ComponentFactory()
{
}

std::vector<std::string> ComponentFactory::getTypesList()
{
	std::vector<std::string> types;
	types.push_back("AdditiveOscillator");
	types.push_back("AmpEnvelope");
	types.push_back("LFO");
	types.push_back("AudioOutput");
	types.push_back("SimpleOscillator");
	types.push_back("Delay");
	types.push_back("Filter");
	types.push_back("NoiseOscillator");
	types.push_back("Envelope");
	return types;
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
	if (type == "NoiseOscillator")
		return new NoiseOscillator();
	if (type == "Envelope")
		return new Envelope();
	return nullptr;
}