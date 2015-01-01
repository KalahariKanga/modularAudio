#include "core.h"
#include "SimpleOscillator.h"
#include "AmpEnvelope.h"
int AudioComponent::n;
int main(int argc, char** argv[])
{
	BASS_Init(-1, SAMPLE_RATE, 0, 0, NULL);
	BASS_SetConfig(BASS_CONFIG_BUFFER, 128);
	BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 10);
	HSTREAM stream;

	stream = BASS_StreamCreate(SAMPLE_RATE, 1, 0, STREAMPROC_PUSH, NULL);
	BASS_ChannelPlay(stream, 0);

	SimpleOscillator simposc;
	AmpEnvelope ampenv;
	ampenv.ins.push_back(&simposc);
	short* output = ampenv.buffer.data;
	simposc.note = Note(440, 128);
	AudioComponent::n = 0;
	while (1)
	{
		simposc.render();
		ampenv.render();
		if (rand() % 100 == 0)
		{
			simposc.note = Note(100 * rand() % 2000, 128);
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