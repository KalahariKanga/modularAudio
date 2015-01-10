#include "Collection.h"


Collection::Collection()
{
	outputComponent = new AudioOutput();
	components.insert(std::pair<std::string,Component*>("output", outputComponent));
}


Collection::~Collection()
{
}

void Collection::update()
{
	for (auto c : components)
	{
		(c.second)->needUpdate = 1;
		(c.second)->note = note;
	}

	outputComponent->update();

	for (auto c : components)
		if ((c.second)->needUpdate)
			(c.second)->update();
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
	p->value = v;
}

void Collection::linkAudio(std::string from, std::string to)
{
	Component* a = components.at(from);
	Component* b = components.at(to);
	((AudioComponent*)a)->outputTo((AudioComponent*)b);
}

void Collection::linkCV(std::string from, std::string param1, std::string to, std::string param2)
{
	Component* a = components.at(from);
	Component* b = components.at(to);
	a->link(param1, b, param2);
}

void Collection::noteDown()
{
	for (auto c : components)
		(c.second)->noteDown();
}

void Collection::noteUp()
{
	for (auto c : components)
		(c.second)->noteUp();
}

bool Collection::isIdle()
{
	if (((AudioComponent*)outputComponent)->buffer.isZero())
		return 1;
	return 0;
}