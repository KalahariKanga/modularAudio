#pragma once
#include "core.h"
#include "AudioBuffer.h"
#include "Note.h"
class AudioComponent
{
public:
	AudioComponent();
	~AudioComponent();
	std::vector<AudioComponent*> ins;
	virtual void render();
	AudioBuffer buffer;
	static int n;
	int startn;
	Note note;
};

