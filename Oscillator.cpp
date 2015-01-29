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
	Note myNote((Notes)(note.note + (int)(12 * octaves.getValue() + semitones.getValue())), note.velocity);
	for (int c = 0; c < BUFFER_LENGTH; c++)
		buffer.data[c] = 256 * note.velocity * getSample(((double)(BUFFER_LENGTH*n + c) / SAMPLE_RATE) * 2 * PI * myNote.frequency);
}

