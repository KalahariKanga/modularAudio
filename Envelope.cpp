#include "Envelope.h"


Envelope::Envelope()
{
	a.create(0.01, 0, 10);
	d.create(0, 0, 10);
	s.create(1, 0, 1);
	r.create(0.5, 0, 10);
	value.create(0, 0, 1, 1);
	parameters.insert(std::pair<std::string, Parameter*>("a", &a));
	parameters.insert(std::pair<std::string, Parameter*>("d", &d));
	parameters.insert(std::pair<std::string, Parameter*>("s", &s));
	parameters.insert(std::pair<std::string, Parameter*>("r", &r));
	parameters.insert(std::pair<std::string, Parameter*>("value", &value));

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