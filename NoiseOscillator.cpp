#include "NoiseOscillator.h"


NoiseOscillator::NoiseOscillator()
{
	addParameter(&type, "type", 0, 0, 0);
	
}


NoiseOscillator::~NoiseOscillator()
{
}

double NoiseOscillator::getSample(double pos)
{
	return (double)(2 * rand() / RAND_MAX) - 1;
}