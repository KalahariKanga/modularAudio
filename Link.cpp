#include "Link.h"


Link::Link()
{
}

Link::Link(Parameter* from, Parameter* to, float amount)
{
	this->from = from;
	this->to = to;
	this->amount = amount;
}
Link::~Link()
{
}

void Link::update()
{
	float v = convertToRange(from->getValue(), from->min, from->max, to->min, to->max);
	to->setValue(v);
}