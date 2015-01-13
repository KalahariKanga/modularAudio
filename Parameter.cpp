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

void Parameter::create(float value, float min, float max, bool readOnly)
{
	this->value = value;
	this->min = min;
	this->max = max;
	this->readOnly = readOnly;
}

void Parameter::setValue(float value)
{
	if (readOnly)
		return;
	this->value = value;
}

float Parameter::getValue()
{
	return value;
}