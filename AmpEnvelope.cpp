#include "AmpEnvelope.h"


AmpEnvelope::AmpEnvelope()
{
	a.create(0.1, 0, 10);
	d.create(0, 0, 10);
	s.create(1, 0, 1);
	r.create(0.5, 0, 10);
	state = 2;
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

	if (state == 1)//note down
	{
		upTime = ((float)(n - startn + 1)*BUFFER_LENGTH) / SAMPLE_RATE;//time passed at the end of this chunk
		
		float timeElapsed = (float)((n - startn)*BUFFER_LENGTH + c) / SAMPLE_RATE;
		//attack phase
		if (timeElapsed <= a.value)
			return timeElapsed / a.value;
		//decay phase
		else if (timeElapsed > a.value && timeElapsed <= a.value + d.value)
			return 1 - ((timeElapsed - a.value)*(1 - s.value)) / d.value;
		//sustain
		else if (timeElapsed > a.value + d.value)
			return s.value;

		
	}
	if (state == 2)//note up
	{
		float releaseTime;
		
		float timeElapsed = (float)((n - startn)*BUFFER_LENGTH + c) / SAMPLE_RATE;
		releaseTime = timeElapsed - upTime;
		if (releaseTime >= r.value)
			return 0;
		return s.value*(1 - releaseTime / r.value);
		

		
	}
}

void AmpEnvelope::noteDown()
{
	state = 1;
	startn = n;
}

void AmpEnvelope::noteUp()
{
	state = 2;
}