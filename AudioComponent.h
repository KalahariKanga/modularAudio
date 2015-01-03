#pragma once
#include "core.h"
#include "AudioBuffer.h"
#include "Note.h"
#include "Parameter.h"
class AudioComponent
{
public:
	AudioComponent();
	~AudioComponent();
	std::vector<AudioComponent*> ins;

	std::map<std::string, Parameter*> parameters;
	std::vector<std::pair<Parameter*, Parameter*>> links;
	Parameter* getParameter(std::string);

	virtual void render();
	void update();
	void outputTo(AudioComponent* other);
	void link(std::string name, AudioComponent* other, std::string othername);
	AudioBuffer buffer;
	static int n;
	int startn;
	Note note;
	
};

