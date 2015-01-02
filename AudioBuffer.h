#pragma once
#include "core.h"
class AudioBuffer
{
public:
	AudioBuffer();
	~AudioBuffer();
	short* data;
	short& operator[](int i);
	void zero();
};

