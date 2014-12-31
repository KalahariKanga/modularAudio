#include "core.h"

int main(int argc, char** argv[])
{
	BASS_Init(-1, SAMPLE_RATE, 0, 0, NULL);
	BASS_SetConfig(BASS_CONFIG_BUFFER, 128);
	BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 10);
	HSTREAM stream;

	stream = BASS_StreamCreate(SAMPLE_RATE, 1, 0, STREAMPROC_PUSH, NULL);
	BASS_ChannelPlay(stream, 0);

	int output[BUFFER_LENGTH];
	for (int c = 0; c < BUFFER_LENGTH; c++)
	{
		output[c] = 0;
	}

	while (1)
	{
		while (BASS_StreamPutData(stream, NULL, 0) > 10){};
		BASS_StreamPutData(stream, (void*)output, BUFFER_LENGTH*sizeof(short));
	}




	BASS_StreamFree(stream);
	BASS_Stop();
	BASS_Free();
}