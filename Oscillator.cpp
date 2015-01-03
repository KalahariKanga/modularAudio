#include "Oscillator.h"


Oscillator::Oscillator()
{
}


Oscillator::~Oscillator()
{
}

void Oscillator::render()
{
	for (int c = 0; c < BUFFER_LENGTH; c++)
		buffer.data[c] = 256 * getSample(((double)(BUFFER_LENGTH*n + c) / SAMPLE_RATE) * 2 * PI * note.frequency);
}
