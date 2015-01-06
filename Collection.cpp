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
		(c.second)->needUpdate = 1;

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