#pragma once
#include "Component.h"
class AudioComponent : public Component
{
public:
	AudioComponent();
	~AudioComponent();
	std::vector<AudioComponent*> ins;

	

	virtual void render();
	void update();
	void outputTo(AudioComponent* other);
	
	AudioBuffer buffer;
	Parameter output;
	
};

