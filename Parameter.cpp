#include "Parameter.h"


Parameter::Parameter()
{
}

Parameter::Parameter(float value, float min, float max)
{
	this->baseValue = value;
	this->value = value;
	this->min = min;
	this->max = max;
}
Parameter::~Parameter()
{
}

void Parameter::create(float value, float min, float max, bool readOnly)
{
	this->baseValue = value;
	this->value = value;
	this->min = min;
	this->max = max;
	this->readOnly = readOnly;
}

void Parameter::setValue(float value)
{
	this->value = value;
	if (readOnly)
		this->baseValue = value;
}

float Parameter::getValue()
{
	return value;
}

void Parameter::setBaseValue(float value)
{
	this->baseValue = value;
	//if (readOnly)
		this->value = value;
}

float Parameter::getBaseValue()
{
	return baseValue;
}