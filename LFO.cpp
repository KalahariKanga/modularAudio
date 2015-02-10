#include "LFO.h"


LFO::LFO()
{
	addParameter(&value, "value", 0, -1, 1, 1);
	addParameter(&freq, "freq", 2, 0, 20);
}


LFO::~LFO()
{
}

void LFO::render()
{
	value.setValue(sin(((double)(BUFFER_LENGTH*n) / SAMPLE_RATE) * 2 * PI * freq.getValue()));
}
