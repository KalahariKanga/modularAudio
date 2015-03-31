#include "Oscillator.h"


Oscillator::Oscillator()
{
	
	addParameter(&octaves, "octaves", 0, -4, 4);
	addParameter(&semitones, "semitones", 0, 0, 12);
	phase = rand() % BUFFER_LENGTH;
}


Oscillator::~Oscillator()
{
}

void Oscillator::render()
{
	Note myNote((Notes)(note.note + (int)(12 * octaves.getValue() + semitones.getValue())), note.velocity);
	for (int c = 0; c < BUFFER_LENGTH; c++)
		buffer.data[c] =  note.velocity * getSample(((double)(BUFFER_LENGTH*n + c + phase) / SAMPLE_RATE) * 2 * PI * myNote.frequency);
}

