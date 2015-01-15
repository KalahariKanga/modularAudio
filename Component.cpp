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

void Component::link(std::string name, Component* other, std::string othername, float amount)
{
	Link l(getParameter(name), other->getParameter(othername), amount);
	links.push_back(l);
}

void Component::noteDown()
{

}

void Component::noteUp()
{

}