#pragma once
#include "core.h"
class Parameter
{
	float value, baseValue;
public:
	Parameter();
	Parameter(float value, float min, float max);
	~Parameter();
	std::string name;//?
	float min, max;
	void create(float value, float min, float max, bool readOnly = 0);
	void setValue(float value);
	void setBaseValue(float value);
	float getValue();
	float getBaseValue();
	bool readOnly;
};

