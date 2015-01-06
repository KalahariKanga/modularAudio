#include "Component.h"


Component::Component()
{
}


Component::~Component()
{
}

void Component::update()
{
	for (auto l : links)
	{
		l.second->value = convertToRange(l.first->value, l.first->min, l.first->max, l.second->min, l.second->max);
	}
	render();
}

void Component::render()
{

}

Parameter* Component::getParameter(std::string name)
{
	return parameters.at(name);
}

void Component::link(std::string name, Component* other, std::string othername)
{
	std::pair<Parameter*, Parameter*> l;
	l.first = getParameter(name);
	l.second = other->getParameter(othername);
	links.push_back(l);
}