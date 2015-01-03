#pragma once
#include "core.h"
class Parameter
{
public:
	Parameter();
	Parameter(float value, float min, float max);
	~Parameter();
	std::string name;//?
	float value, min, max;
	void create(float value, float min, float max);
};

