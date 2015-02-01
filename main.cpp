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
	synth.addComponent("osc1", "SimpleOscillator");
	synth.addComponent("osc2", "SimpleOscillator");
	synth.addComponent("ampenv1", "AmpEnvelope");
	synth.addComponent("ampenv2", "AmpEnvelope");
	synth.addComponent("env", "Envelope");
	synth.addComponent("delay", "Delay");
	synth.addComponent("filter", "Filter");	

	synth.addComponent("lfo", "LFO");

	synth.setParameterRaw("lfo", "freq", 0.5);
	synth.setParameterRaw("osc1", "waveform", 2);
	synth.setParameterRaw("osc2", "waveform", 0);
	synth.setParameterRaw("ampenv1", "a", 0.1f);
	synth.setParameterRaw("ampenv2", "a", 0.1f);

	synth.linkCV("lfo", "value", "osc1", "pulseWidth", 0.5);
	synth.linkCV("env", "value", "osc1", "semitones", 0.5);
	synth.linkAudio("osc1", "ampenv1");
	synth.linkAudio("osc2", "ampenv2");
	synth.linkAudio("ampenv1", "delay");
	synth.linkAudio("ampenv2", "delay");
	synth.linkAudio("delay", "filter");
	synth.linkAudio("filter", "output");
	
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