#include "Environment.h"


Environment::Environment()
{
	
}


Environment::~Environment()
{
}

Synth* Environment::addSynth()
{
	synths.push_back(new Synth());
	return synths.back();
}

Synth* Environment::addSynth(std::string filename)
{
	synths.push_back(new Synth());
	synths.back()->loadPatch(filename);
	return synths.back();
}

short* Environment::getBuffer()
{
	return buffer.data;
}

void Environment::update()
{
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	//play midi file
	if (midiFileIsPlaying)
	{
		midiTicks += 350;// elapsed_seconds.count() / tickLength;
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
					//std::cout << "Note down!" << n << "\n";
					events.push_back(midifile[t][midiEventCount[t]]);
				}
				if (midifile[t][midiEventCount[t]].isNoteOff())
				{
					Notes n = (Notes)(midifile[t][midiEventCount[t]].getKeyNumber() - 1);
					int v = midifile[t][midiEventCount[t]].getP2();
					if (synthMap.find(t) != synthMap.end())
						synthMap[t]->noteUp(Note(n, v));
					//std::cout << "Note up!\n";
					events.push_back(midifile[t][midiEventCount[t]]);
				}
				midiEventCount[t]++;
			}
		}
	}
	start = std::chrono::system_clock::now();
	



	buffer.zero();
	//update synths
	for (auto s : synths)
		s->update();
	//collate buffers
	for (auto s : synths)
	{
		for (int c = 0; c < BUFFER_LENGTH; c++)
			buffer[c] += s->getBuffer()[c];
	}
	
	AudioComponent::n++;
}

void Environment::loadMidiFile(std::string fname)
{
	midifile.read(fname);
}

void Environment::assignMidiTrack(int track, Synth* s)
{
	synthMap.insert(std::pair<int, Synth*>(track, s));
}

void Environment::playMidiFile()
{
	midiFileIsPlaying = 1;
	midifile.absoluteTicks();
	tickLength = 60000 / (midifile.getTicksPerQuarterNote() * 120);
	start = std::chrono::system_clock::now();
}