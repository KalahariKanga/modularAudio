#pragma once
#include "core.h"
#include "AudioBuffer.h"
#include "Note.h"
#include "Parameter.h"
#include "Link.h"

class Component
{
public:
	Component();
	~Component();
	std::map<std::string, Parameter*> parameters;
	std::vector<Link> links;
	Parameter* getParameter(std::string);
	virtual void update();
	virtual void render();
	void link(std::string name, Component* other, std::string othername);
	static int n;
	int startn;
	Note note;
	bool needUpdate;
	virtual void noteDown();
	virtual void noteUp();
	
};

