#include "AmpEnvelope.h"


AmpEnvelope::AmpEnvelope()
{
	a.create(0.01, 0, 10);
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
		if (timeElapsed <= a.getValue())
			return timeElapsed / a.getValue();
		//decay phase
		else if (timeElapsed > a.getValue() && timeElapsed <= a.getValue() + d.getValue())
			return 1 - ((timeElapsed - a.getValue())*(1 - s.getValue())) / d.getValue();
		//sustain
		else if (timeElapsed > a.getValue() + d.getValue())
			return s.getValue();

		
	}
	if (state == 2)//note up
	{
		float releaseTime;
		
		float timeElapsed = (float)((n - startn)*BUFFER_LENGTH + c) / SAMPLE_RATE;
		releaseTime = timeElapsed - upTime;
		if (releaseTime >= r.getValue())
			return 0;
		return s.getValue()*(1 - releaseTime / r.getValue());
		

		
	}
	return 0;
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