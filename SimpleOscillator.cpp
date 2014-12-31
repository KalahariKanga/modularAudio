#include "SimpleOscillator.h"


SimpleOscillator::SimpleOscillator()
{
}


SimpleOscillator::~SimpleOscillator()
{
}

void SimpleOscillator::render()
{
	for (int c = 0; c < BUFFER_LENGTH; c++)
		buffer.data[c] = 512 * sin((float)(n*BUFFER_LENGTH + c) / 20);
}