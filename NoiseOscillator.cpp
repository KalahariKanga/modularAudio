#include "NoiseOscillator.h"


NoiseOscillator::NoiseOscillator()
{
	type.create(0, 0, 0);
	parameters.insert(std::pair<std::string, Parameter*>("type", &type));
}


NoiseOscillator::~NoiseOscillator()
{
}

double NoiseOscillator::getSample(double pos)
{
	return (double)(2 * rand() / RAND_MAX) - 1;
}