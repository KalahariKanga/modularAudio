#pragma once
#include "Parameter.h"
class Link
{
public:
	Link();
	Link(Parameter* from, Parameter* to, float amount);
	~Link();
	Parameter* from;
	Parameter* to;
	float amount;
	void update();
	/*
	Parameter* scale;
	float scaleAmount;
	*/
};

