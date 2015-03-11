#pragma once
#include "core.h"
class __declspec(dllexport) Note
{
public:
	Note();
	Note(Notes note, int v);
	~Note();
	Notes note;
	int frequency;
	int velocity;
	void updateFrequency();
};

