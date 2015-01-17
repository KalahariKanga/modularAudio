#include "Synth.h"
#include <chrono>
#include <thread>

int main(int argc, char** argv[])
{
	BASS_Init(-1, SAMPLE_RATE, 0, 0, NULL);
	BASS_SetConfig(BASS_CONFIG_BUFFER, 128);
	BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 10);
	HSTREAM stream;

	stream = BASS_StreamCreate(SAMPLE_RATE, 1, 0, STREAMPROC_PUSH, NULL);
	BASS_ChannelPlay(stream, 0);

	


	srand(time(0));

	Synth synth;
	Collection collection;
	synth.addComponent("osc", "SimpleOscillator");
	synth.addComponent("ampenv", "AmpEnvelope");
	synth.addComponent("lfo", "LFO");
	//synth.linkCV("osc", "output", "osc", "semitones",1);
	synth.setParameterRaw("osc", "waveform", 0);
	synth.linkAudio("osc", "ampenv");
	synth.linkAudio("ampenv", "output");
	
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

		if (AudioComponent::n % 75 == 50)
			synth.noteDown(Note((Notes)(rand() % 60 + 20), 100));
		while (BASS_StreamPutData(stream, NULL, 0) > 10){};
		BASS_StreamPutData(stream, (void*)output, BUFFER_LENGTH*sizeof(short));
		AudioComponent::n++;
	}




	BASS_StreamFree(stream);
	BASS_Stop();
	BASS_Free();
}