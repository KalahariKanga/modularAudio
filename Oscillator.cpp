#include "Oscillator.h"


Oscillator::Oscillator()
{
	octaves.create(0, -4, 4);
	semitones.create(0, 0, 12);
	parameters.insert(std::pair<std::string, Parameter*>("octaves", &octaves));
	parameters.insert(std::pair<std::string, Parameter*>("semitones", &semitones));
}


Oscillator::~Oscillator()
{
}

void Oscillator::render()
{
	Note myNote((Notes)(note.note + (int)(12 * octaves.value + semitones.value)), note.velocity);
	for (int c = 0; c < BUFFER_LENGTH; c++)
		buffer.data[c] = 256 * getSample(((double)(BUFFER_LENGTH*n + c) / SAMPLE_RATE) * 2 * PI * myNote.frequency);
}

