#include "AdditiveOscillator.h"


AdditiveOscillator::AdditiveOscillator()
{
	for (int c = 0; c < 64; c++)
	{
		addParameter(&amount[c], "amount" + std::to_string(c), 0, 0, 1);
	}
	amount[0].setValue(1);
	amount[2].setValue(0.5);
	amount[4].setValue(0.25);
	amount[6].setValue(0.125);
}


AdditiveOscillator::~AdditiveOscillator()
{
}

double AdditiveOscillator::getSample(double pos)
{
	
	double value = 0;
	for (int c = 0; c < 16; c++)
		value += amount[c].getValue() * sin((c + 1)*pos);
	return value;
}