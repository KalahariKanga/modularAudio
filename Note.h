#pragma once
#include "core.h"
class Note
{
public:
	Note();
	Note(Notes note, int v);
	Note(sf::Keyboard::Key key, int v);
	~Note();
	Notes note;
	int frequency;
	int velocity;
	void updateFrequency();
};

