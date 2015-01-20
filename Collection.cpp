#include "Collection.h"


Collection::Collection()
{
	outputComponent = new AudioOutput();
	components.insert(std::pair<std::string,Component*>("output", outputComponent));
	noteState = 0;
}


Collection::~Collection()
{
}

void Collection::update()
{
	for (auto l : links)
	{
		l.update();
	}

	for (auto c : components)
	{
		(c.second)->needUpdate = 1;
		(c.second)->note = note;
	}

	outputComponent->update();

	for (auto c : components)
		if ((c.second)->needUpdate)
			(c.second)->update();
	
	if (isIdle())
		note = Note(NONOTE, 0);
}

void Collection::addComponent(std::string name, std::string type)
{
	Component* c = ComponentFactory::makeComponent(type);
	components.insert(std::pair<std::string, Component*>(name, c));
}

void Collection::setParameter(std::string component, std::string parameter, float value)
{
	Parameter* p = components.at(component)->parameters.at(parameter);
	float v = convertToRange(value, 0, 1, p->min, p->max);
	p->setBaseValue(value);
}

void Collection::setParameterRaw(std::string component, std::string parameter, float value)
{
	Parameter* p = components.at(component)->parameters.at(parameter);
	p->setBaseValue(value);
}

void Collection::linkAudio(std::string from, std::string to)
{
	Component* a = components.at(from);
	Component* b = components.at(to);
	((AudioComponent*)a)->outputTo((AudioComponent*)b);

}

void Collection::linkCV(std::string from, std::string param1, std::string to, std::string param2, float amount)
{
	Component* a = components.at(from);
	Component* b = components.at(to);
	Link link(a->getParameter(param1), b->getParameter(param2), amount);
	links.push_back(link);
}

void Collection::noteDown()
{
	for (auto c : components)
		(c.second)->noteDown();
	noteState = 1;
}

void Collection::noteUp()
{
	for (auto c : components)
		(c.second)->noteUp();
	noteState = 0;
}

bool Collection::isIdle()
{
	if (((AudioComponent*)outputComponent)->buffer.isZero())
		return 1;
	return 0;
}