#include "AdditiveOscillator.h"


AdditiveOscillator::AdditiveOscillator()
{
	for (int c = 0; c < 64; c++)
	{
		amount[c] = 0;
		std::pair<std::string, float*> p;
		p.first = "amount" + std::to_string(c);
		p.second = &amount[c];
		parameters.insert(p);
	}
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
		value += amount[c] * sin((c+1)*pos);
	return value;
}