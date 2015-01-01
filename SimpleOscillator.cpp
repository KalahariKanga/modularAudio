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
		buffer.data[c] = 256 * sin(((double)(BUFFER_LENGTH*n + c) / SAMPLE_RATE) * 2 * PI * note.frequency);
}