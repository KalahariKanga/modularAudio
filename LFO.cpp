#include "LFO.h"


LFO::LFO()
{
	freq = 0.5;
	parameters.insert(std::pair<std::string, float*>("lfo", &value));
	parameters.insert(std::pair<std::string, float*>("frequency", &freq));
}


LFO::~LFO()
{
}

void LFO::render()
{
	value = sin(((double)(BUFFER_LENGTH*n) / SAMPLE_RATE) * 2 * PI * freq);
}
