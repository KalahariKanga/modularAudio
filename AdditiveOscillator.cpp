#include "AdditiveOscillator.h"


AdditiveOscillator::AdditiveOscillator()
{
	for (int c = 0; c < 64; c++)
	{
		amount[c].value = 0;
		amount[c].min = 0;
		amount[c].max = 1;
		std::string name = "amount" + std::to_string(c);
		parameters.insert(std::pair<std::string, Parameter*>(name, &amount[c]));
	}
	amount[0].value = 1;
	amount[2].value = 0.5;
	amount[4].value = 0.25;
	amount[6].value = 0.125;
}


AdditiveOscillator::~AdditiveOscillator()
{
}

double AdditiveOscillator::getSample(double pos)
{
	
	double value = 0;
	for (int c = 0; c < 16; c++)
		value += amount[c].value * sin((c+1)*pos);
	return value;
}