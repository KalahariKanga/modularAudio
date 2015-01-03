#include "AdditiveOscillator.h"


AdditiveOscillator::AdditiveOscillator()
{
	for (int c = 0; c < 64; c++)
		amount[c] = 0;
	amount[0] = 1;
	amount[2] = 0.5;
	amount[4] = 0.25;
	amount[6] = 0.125;
}


AdditiveOscillator::~AdditiveOscillator()
{
}

double AdditiveOscillator::getSample(double pos)
{
	double value = 0;
	for (int c = 0; c < 64; c++)
		value += sin(c*pos);
	return value;
}