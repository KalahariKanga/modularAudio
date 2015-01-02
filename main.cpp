#include "core.h"
#include "SimpleOscillator.h"
#include "AmpEnvelope.h"
#include "AudioOutput.h"


int main(int argc, char** argv[])
{
	BASS_Init(-1, SAMPLE_RATE, 0, 0, NULL);
	BASS_SetConfig(BASS_CONFIG_BUFFER, 128);
	BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 10);
	HSTREAM stream;

	stream = BASS_StreamCreate(SAMPLE_RATE, 1, 0, STREAMPROC_PUSH, NULL);
	BASS_ChannelPlay(stream, 0);


	SimpleOscillator simposc1, simposc2;
	AmpEnvelope ampenv;
	AudioOutput audiooutput;
	simposc1.linkTo(&ampenv);
	simposc2.linkTo(&ampenv);
	ampenv.linkTo(&audiooutput);

	short* output = audiooutput.buffer.data;
	simposc1.note = Note(c4, 128);
	simposc2.note = Note(ds4, 128);


	AudioComponent::n = 0;
	while (1)
	{
		audiooutput.update();
		if (rand() % 100 == 0)
		{
			simposc1.note = Note((Notes)(rand() % 108), 128);
			simposc2.note = Note((Notes)(rand() % 108), 128);
			ampenv.noteDown();
		}
		while (BASS_StreamPutData(stream, NULL, 0) > 10){};
		BASS_StreamPutData(stream, (void*)output, BUFFER_LENGTH*sizeof(short));
		AudioComponent::n++;
	}




	BASS_StreamFree(stream);
	BASS_Stop();
	BASS_Free();
}