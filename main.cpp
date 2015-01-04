#include "core.h"
#include "SimpleOscillator.h"
#include "AmpEnvelope.h"
#include "AdditiveOscillator.h"
#include "AudioOutput.h"
#include "LFO.h"


int main(int argc, char** argv[])
{
	BASS_Init(-1, SAMPLE_RATE, 0, 0, NULL);
	BASS_SetConfig(BASS_CONFIG_BUFFER, 128);
	BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 10);
	HSTREAM stream;

	stream = BASS_StreamCreate(SAMPLE_RATE, 1, 0, STREAMPROC_PUSH, NULL);
	BASS_ChannelPlay(stream, 0);


	AdditiveOscillator osc;
	AmpEnvelope ampenv;
	AudioOutput audiooutput;
	LFO lfo;

	osc.outputTo(&ampenv);
	ampenv.outputTo(&audiooutput);
	lfo.link("lfo", &osc, "amount1");
	lfo.link("lfo", &osc, "amount3");
	lfo.link("lfo", &osc, "amount5");
	

	short* output = audiooutput.buffer.data;
	osc.note = Note(c2, 128);
	

	bool which = 0;//dbg
	AudioComponent::n = 0;
	while (1)
	{
		lfo.update();
		audiooutput.update();
		if (rand() % 50 == 0)
		{
			//osc.note = Note((Notes)(rand() % 108), 128);
			if (which)
			{
				which = 0;
				ampenv.noteUp();
			}
			else
			{
				which = 1;
				ampenv.noteDown();
			}
			
		}
		while (BASS_StreamPutData(stream, NULL, 0) > 10){};
		BASS_StreamPutData(stream, (void*)output, BUFFER_LENGTH*sizeof(short));
		AudioComponent::n++;
	}




	BASS_StreamFree(stream);
	BASS_Stop();
	BASS_Free();
}