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
		l.update();
	}
	render();
	needUpdate = 0;
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
	links.push_back(Link(getParameter(name), other->getParameter(othername),1));
}

void Component::noteDown()
{

}

void Component::noteUp()
{

}