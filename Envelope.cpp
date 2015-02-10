#include "Envelope.h"


Envelope::Envelope()
{
	addParameter(&a, "a", 0.001, 0, 10);
	addParameter(&d, "d", 0, 0, 10);
	addParameter(&s, "s", 1, 0, 1);
	addParameter(&r, "r", 0.5, 0, 10);
	addParameter(&value, "value", 0, 0, 1, 1);
	state = 2;

}


Envelope::~Envelope()
{
}

void Envelope::update()
{
	if (state == 1)
	{
		upTime = ((float)(n - startn + 1)*BUFFER_LENGTH) / SAMPLE_RATE;
		float timeElapsed = (float)((n - startn)*BUFFER_LENGTH) / SAMPLE_RATE;
		//attack phase
		if (timeElapsed <= a.getValue())
			v = timeElapsed / a.getValue();
		//decay phase
		else if (timeElapsed > a.getValue() && timeElapsed <= a.getValue() + d.getValue())
			v = 1 - ((timeElapsed - a.getValue())*(1 - s.getValue())) / d.getValue();
		//sustain
		else if (timeElapsed > a.getValue() + d.getValue())
			v = s.getValue();

		releaseValue = v;
		value.setValue(v);
	}
	if (state == 2)//note up
	{
		float releaseTime;

		float timeElapsed = (float)((n - startn)*BUFFER_LENGTH ) / SAMPLE_RATE;
		releaseTime = timeElapsed - upTime;
		if (releaseTime >= r.getValue())
			v = 0;
		value.setValue(v*(1 - releaseTime / r.getValue()));
	}
}

void Envelope::noteDown()
{
	state = 1;
	startn = n;
}

void Envelope::noteUp()
{
	state = 2;
}