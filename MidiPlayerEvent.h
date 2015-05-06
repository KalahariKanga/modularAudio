#pragma once

#include "MidiEvent.h"
class _declspec(dllexport) MidiPlayerEvent
{
public:
	MidiPlayerEvent(MidiEvent, int);
	~MidiPlayerEvent();
	MidiEvent midievent;
	int playerID;
};

