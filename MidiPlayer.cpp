#include "MidiPlayer.h"


MidiPlayer::MidiPlayer(std::string fname)
{
	loadFile(fname);
}


MidiPlayer::~MidiPlayer()
{
}

void MidiPlayer::update(float delta)
{
	if (isPlaying)
	{
		midiTicks += 350;// something something delta
		for (int t = 1; t < midifile.getNumTracks(); t++)
		{
			while (midifile[t].getSize() > midiEventCount[t] && midifile[t][midiEventCount[t]].tick < midiTicks)
			{
				if (midifile[t][midiEventCount[t]].isNoteOn())
				{
					Notes n = (Notes)(midifile[t][midiEventCount[t]].getKeyNumber() - 1);
					int v = midifile[t][midiEventCount[t]].getP2();
					if (synthMap.find(t) != synthMap.end())
						synthMap[t]->noteDown(Note(n, v));
					
					events.push_back(midifile[t][midiEventCount[t]]);
				}
				if (midifile[t][midiEventCount[t]].isNoteOff())
				{
					Notes n = (Notes)(midifile[t][midiEventCount[t]].getKeyNumber() - 1);
					int v = midifile[t][midiEventCount[t]].getP2();
					if (synthMap.find(t) != synthMap.end())
						synthMap[t]->noteUp(Note(n, v));
					
					events.push_back(midifile[t][midiEventCount[t]]);
				}
				midiEventCount[t]++;
			}
		}
	}
}

void MidiPlayer::loadFile(std::string fname)
{
	midifile.read(fname);
}

void MidiPlayer::assignTrack(int track, Synth* s)
{
	synthMap.insert(std::pair<int, Synth*>(track, s));
}

void MidiPlayer::play()
{
	isPlaying = 1;
	midifile.absoluteTicks();
	tickLength = 60000 / (midifile.getTicksPerQuarterNote() * 120);
}