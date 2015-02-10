#include "Synth.h"
#include <chrono>
#include <thread>

int main(int argc, char** argv[])
{
	BASS_Init(-1, SAMPLE_RATE, 0, 0, NULL);
	BASS_SetConfig(BASS_CONFIG_BUFFER, 128);
	BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 10);
	HSTREAM stream = BASS_StreamCreate(SAMPLE_RATE, 1, 0, STREAMPROC_PUSH, NULL);
	BASS_ChannelPlay(stream, 0);

	srand(time(0));

	Synth synth;
	
	synth.loadPatch("test.out");
	//synth.savePatch("test.out");
	short* output = synth.buffer.data;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	AudioComponent::n = 0;
	while (1)
	{
		
		start = std::chrono::system_clock::now();
		synth.update();
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		//std::cout << elapsed_seconds.count() << std::endl;

		while (BASS_StreamPutData(stream, NULL, 0) > 10){};
		BASS_StreamPutData(stream, (void*)output, BUFFER_LENGTH*sizeof(short));
		AudioComponent::n++;
	}

	BASS_StreamFree(stream);
	BASS_Stop();
	BASS_Free();
}