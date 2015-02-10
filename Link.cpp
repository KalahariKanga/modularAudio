#include "Link.h"


Link::Link()
{
	amount = 0;
}

Link::Link(std::string fromComponent, Parameter* from, std::string toComponent, Parameter* to, float amount)
{
	this->from = from;
	this->to = to;
	this->amount = amount;
	this->fromComponent = fromComponent;
	this->toComponent = toComponent;
}
Link::~Link()
{
}

void Link::update()
{
	float v = convertToRange(from->getBaseValue(), from->min, from->max, to->min, to->max*amount);
	to->setValue(v);
}