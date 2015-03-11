#pragma once
#include "core.h"
class __declspec(dllexport) AudioBuffer //TODO: really shouldnt have to do this
{
public:
	AudioBuffer();
	~AudioBuffer();
	short* data;
	short& operator[](int i);
	void zero();
	bool isZero();
};

