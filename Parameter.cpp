#include "Parameter.h"


Parameter::Parameter()
{
}

Parameter::Parameter(float value, float min, float max)
{
	this->value = value;
	this->min = min;
	this->max = max;
}
Parameter::~Parameter()
{
}

void Parameter::create(float value, float min, float max)
{
	this->value = value;
	this->min = min;
	this->max = max;
}