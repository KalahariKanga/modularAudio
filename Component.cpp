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

void Component::addParameter(Parameter* param, std::string name, float value, float min, float max, bool readOnly)
{
	param->create(name, value, min, max, readOnly);
	parameters.insert(std::pair<std::string, Parameter*>(name, param));
}

std::vector<std::string> Component::getParameterList()
{
	std::vector<std::string> list;
	for (auto p : parameters)
	{
		list.push_back((p.second)->name);
	}
	return list;
}