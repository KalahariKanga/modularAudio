#pragma once
#include "core.h"
class Parameter
{
	float value;
public:
	Parameter();
	Parameter(float value, float min, float max);
	~Parameter();
	std::string name;//?
	float min, max;
	void create(float value, float min, float max, bool readOnly = 0);
	void setValue(float value);
	float getValue();
	bool readOnly;
};

