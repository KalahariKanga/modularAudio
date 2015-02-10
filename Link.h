#pragma once
#include "Parameter.h"
class Link
{
public:
	Link();
	Link::Link(std::string fromComponent, Parameter* from, std::string toComponent, Parameter* to, float amount);
	~Link();
	std::string fromComponent, toComponent;
	Parameter* from;
	Parameter* to;
	float amount;
	void update();
	/*
	Parameter* scale;
	float scaleAmount;
	*/
};

