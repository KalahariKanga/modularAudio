#include "AmpEnvelope.h"


AmpEnvelope::AmpEnvelope()
{
	
}


AmpEnvelope::~AmpEnvelope()
{
}

void AmpEnvelope::render()
{
	for (int c = 0; c < BUFFER_LENGTH; c++)
	{
		buffer.data[c] = 0;
		for (auto i : ins)
		{
			buffer.data[c] += i->buffer.data[c] * envelope(c);
		}
	}
}

float AmpEnvelope::envelope(int c)
{
	float v = 1 - (float)((n - startn)*BUFFER_LENGTH + c) / 44100;
	if (v >= 0)
		return v;
	return 0;
}

void AmpEnvelope::noteDown()
{
	startn = n;
}