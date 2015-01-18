#include "Component.h"


Component::Component()
{
	
}


Component::~Component()
{
}

void Component::update()
{
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

void Component::noteDown()
{

}

void Component::noteUp()
{

}