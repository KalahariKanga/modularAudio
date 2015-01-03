#include "LFO.h"


LFO::LFO()
{
	value.create(0, -1, 1);
	freq.create(2, 0, 20);
	parameters.insert(std::pair<std::string, Parameter*>("lfo", &value));
	parameters.insert(std::pair<std::string, Parameter*>("frequency", &freq));
}


LFO::~LFO()
{
}

void LFO::render()
{
	value.value = sin(((double)(BUFFER_LENGTH*n) / SAMPLE_RATE) * 2 * PI * freq.value);
}
