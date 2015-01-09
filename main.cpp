#include "Synth.h"


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
	synth.addComponent("osc", "AdditiveOscillator");
	synth.addComponent("ampenv", "AmpEnvelope");
	synth.addComponent("lfo", "LFO");
	synth.linkCV("lfo", "lfo", "osc", "amount1");
	synth.linkAudio("osc", "ampenv");
	synth.linkAudio("ampenv", "output");
	
	short* output = synth.buffer.data;
	
	AudioComponent::n = 0;
	while (1)
	{
		synth.update();
		/*if (rand() % 100 == 0)
		{
			
			if (which)
			{
				
				which = 0;
				collection.noteUp();
			}
			else
			{
				collection.note = Note((Notes)(rand() % 108), 128);
				which = 1;
				collection.noteDown();
			}
			
		}*/
		if (AudioComponent::n % 100 == 50)
			synth.noteDown(Note((Notes)(rand() % 60 + 20), 100));
		while (BASS_StreamPutData(stream, NULL, 0) > 10){};
		BASS_StreamPutData(stream, (void*)output, BUFFER_LENGTH*sizeof(short));
		AudioComponent::n++;
	}




	BASS_StreamFree(stream);
	BASS_Stop();
	BASS_Free();
}