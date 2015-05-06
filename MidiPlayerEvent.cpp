#include "MidiPlayerEvent.h"


MidiPlayerEvent::MidiPlayerEvent(MidiEvent e, int p)
{
	midievent = e;
	playerID = p;
}


MidiPlayerEvent::~MidiPlayerEvent()
{
}
