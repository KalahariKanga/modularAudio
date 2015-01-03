#include "SimpleOscillator.h"


SimpleOscillator::SimpleOscillator()
{
}


SimpleOscillator::~SimpleOscillator()
{
}

double SimpleOscillator::getSample(double pos)
{
	return sin(pos);
}