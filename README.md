# ModularAudio
===
Classes
---
### Environment
- `Synth* addSynth()`  
Add an empty `Synth` to the environment, and return a pointer to it.  
- `Synth* addSynth(std::string filename)`  
Create a `Synth`, load the synth patch `filename` and return a pointer to it.  
- `short* getBuffer()`  
Get a pointer to the current output buffer of the environment.  
- `MidiPlayer* addPlayer(std::string filename)`  

- `void update()`  
Render the next buffer
### Synth
- `void addComponent(const std::string& name, const std::string& type)`  
Add a new component, with name `name` and of type `type`.  
- `void setParameter(std::string component, std::string parameter, float value)`  
Set `component`'s parameter named `parameter` to `value`, in the normalised range [0,1].  
- `void setParameterRaw(std::string component, std::string parameter, float value)`  
Set `component`'s parameter named `parameter` to `value`, in the range defined by the parameter.    
- `void linkAudio(std::string from, std::string to)`  
Create an audio link from the component `from` to the component `to`. All audio produced by `from` will be sent to `to`.   
- `void linkCV(std::string from, std::string param1, std::string to, std::string param2, float amount)`  
Create a CV link from `from.param1` to `to.param2`, where `param1` has `amount` influence on `param2`.
- `void noteDown(Note note)`  
Trigger the note `note` to be played.
- `void noteUp(Note note)`  
Stop playing the note `note`.
- `short* getBuffer()`  
Get a pointer to the output buffer of the synth.  
- `Component* getComponent(std::string name)`  
Get a pointer to the component with name `name`.
- `void savePatch(std::string fname)`  
Save the current patch, with file name `fname`.  
- `void loadPatch(std::string fname)`  
Load the patch with filename `fname`.  
- `void playNoteDuration(Note note, float seconds)`  
Play the note `note` for `seconds` seconds.

Components
---
### SimpleOscillator
An oscillator which generates the simplest waveforms, including sine, square and sawtooth.  
**Parameters**  
- `waveform` - The waveform type to generate.  
Range: 0 - 3, Default: 0  
- `pulseWidth` - For pulse and sawtooth waves, the width of the pulse.  
Range: 0 - 1, Default: 0.5  
### AdditiveOscillator  
An oscillator which sums sine harmonics  
**Parameters**  
- `amount[n]` - How much of the n <sup>th</sup> harmonic to use. (0 <= n < 64)  
Range: 0 - 1, Default: 0  
### NoiseOscillator  
Produces white noise  
### AmpEnvelope  
An ADSR envlope for audio volume.  
**Parameters**  
- `a` - Attack time, in seconds  
Range: 0 - 10, Default: 0.01  
- `d` - Decay time, in seconds  
Range: 0 - 10, Default: 0.1  
- `s` - Sustain level  
Range 0 - 1, Default: 0.8  
- `r` - Release time, in seconds  
Range 0 - 10, Default: 0.1  
