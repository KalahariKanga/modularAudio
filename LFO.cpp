#include "LFO.h"


LFO::LFO()
{
	value.create(0, -1, 1, 1);
	freq.create(2, 0, 20);
	parameters.insert(std::pair<std::string, Parameter*>("value", &value));
	parameters.insert(std::pair<std::string, Parameter*>("freq", &freq));
}


LFO::~LFO()
{
}

void LFO::render()
{
	value.setValue(sin(((double)(BUFFER_LENGTH*n) / SAMPLE_RATE) * 2 * PI * freq.getValue()));
}
