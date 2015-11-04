# ModularAudio
===
Classes
---
### Environment
`Synth* addSynth()` - add an empty `Synth` to the environment, and return a pointer to it.  
`Synth* addSynth(std::string filename)` - create a `Synth`, load the synth patch `filename` and return a pointer to it.  
`short* getBuffer()` - get a pointer to the current output buffer of the environment.  
`MidiPlayer* addPlayer(std::string filename)` -  
`void update()` - render the next buffer
### Synth
`void addComponent(const std::string& name, const std::string& type)` - add a new component, with name `name` and of type `type`  
`void setParameter(std::string component, std::string parameter, float value)` -  set `component`'s parameter named `parameter` to `value`, in the normalised range [0,1].  
`void setParameterRaw(std::string component, std::string parameter, float value)` - set `component`'s parameter named `parameter` to `value`.  
`void linkAudio(std::string from, std::string to)` - create an audio link from the component `from` to the component `to`.  
`void linkCV(std::string from, std::string param1, std::string to, std::string param2, float amount)` -  
`void noteDown(Note note)` -  
`void noteUp(Note note)` -  
`short* getBuffer()` -  
`Component* getComponent(std::string name)` -  
`void savePatch(std::string fname)` -  
`void loadPatch(std::string fname)` -  
`void playNoteDuration(Note note, float seconds)` -  

Components
---
### SimpleOscillator
An oscillator which generates the simplest waveforms, including sine, square and sawtooth.  
**Parameters**  
`waveform` - the waveform type to generate.  
`pulseWidth` - for pulse and sawtooth waves, the width of the pulse.
