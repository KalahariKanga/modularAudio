#include "Synth.h"
#include <iostream>
#include <fstream>

Synth::Synth()
{
	for (int c = 0; c < polyphony; c++)
	{
		collections.push_back(new Collection);
		//something something delete...
	}

	for (int c = 0; c < 100; c++)
		noteUpTimer[c] = -1;
	
}

Synth::~Synth()
{
}

void Synth::update()
{
	activeNotes = 0;
	for (auto c : collections)
	{
		c->update();
		if (!c->isIdle())
			activeNotes++;
	}
	buffer.zero();
	for (auto c : collections)
		for (int t = 0; t < BUFFER_LENGTH; t++)
			buffer.data[t] += ((AudioComponent*)(c->outputComponent))->buffer.data[t];

	//release any queued notes
	for (int c = 0; c < 100; c++)
	{
		if (noteUpTimer[c] > 0)
		{
			noteUpTimer[c] -= (float)BUFFER_LENGTH / SAMPLE_RATE;
			if (noteUpTimer[c] <= 0)
				noteUp(Note((Notes)c, 0));
		}
	}
}

void Synth::addComponent(const std::string& name, const std::string& type)
{
	std::cout << name << " " << type << std::endl;
	for (auto c : collections)
		c->addComponent(name, type);
}

void Synth::setParameter(std::string component, std::string parameter, float value)
{
	for (auto c : collections)
	{
		c->setParameter(component, parameter, value);
	}
}

void Synth::setParameterRaw(std::string component, std::string parameter, float value)
{
	for (auto c : collections)
	{
		c->setParameterRaw(component, parameter, value);
	}
}

void Synth::linkAudio(std::string from, std::string to)
{
	for (auto c : collections)
		c->linkAudio(from, to);
}

void Synth::linkCV(std::string from, std::string param1, std::string to, std::string param2, float amount)
{
	for (auto c : collections)
		c->linkCV(from, param1, to, param2, amount);
}

void Synth::noteDown(Note note)
{
	for (auto c : collections)
		if (c->note.note == note.note && c->noteState == 1)
			return;
	for (auto c : collections)
		if (c->isIdle())
		{
			c->setIdle(0);
			c->note = note;
			c->noteDown();
			return;
		}
	//if all components are active
}

void Synth::noteUp(Note note)
{
	for (auto c : collections)
		if (c->note.note == note.note)
			c->noteUp();
}

short* Synth::getBuffer()
{
	return buffer.data;
}

Component* Synth::getComponent(std::string name)
{
	return collections[0]->components.at(name);
}

void Synth::loadPatch(std::string fname)
{
	std::ifstream stream;
	stream.open(fname);
	//components
	int n;
	stream >> n;
	for (int c = 0; c < n; c++)
	{
		std::string name, type;
		stream >> name >> type;
		addComponent(name, type);
	}
	//audio links
	stream >> n;
	for (int c = 0; c < n; c++)
	{
		std::string from, to;
		stream >> from >> to;
		linkAudio(from, to);
	}
	//cv links
	stream >> n;
	for (int c = 0; c < n; c++)
	{
		std::string from, param1, to, param2;
		float amount;
		stream >> from >> param1 >> to >> param2 >> amount;
		linkCV(from, param1, to, param2, amount);
	}
	//set raw parameters
	stream >> n;
	for (int c = 0; c < n; c++)
	{
		std::string component, param;
		float value;
		stream >> component >> param >> value;
		setParameterRaw(component, param, value);
	}
}

void Synth::savePatch(std::string fname)
{
	std::ofstream stream;
	stream.open(fname);
	//components
	int n = collections[0]->components.size() - 1; //to account for AudioOutput
	stream << n << std::endl;
	for (auto c : collections[0]->components)
	{
		//remove leading "class "
		std::string classname = std::string(typeid(*c.second).name()).erase(0,6);

		if (classname != "AudioOutput")
			stream << c.first << " " << classname << std::endl;
	}

	//audio links
	n = 0;
	for (auto c : collections[0]->components)
	{
		if (dynamic_cast<AudioComponent*>(c.second))
		{
			n += (dynamic_cast<AudioComponent*>(c.second))->ins.size();
		}
	}
	stream << n << std::endl;
	for (auto c : collections[0]->components)
	{
		if (dynamic_cast<AudioComponent*>(c.second))
		{
			for (auto d : (dynamic_cast<AudioComponent*>(c.second))->ins)
			{
				stream << d->name << " " << c.second->name << std::endl;
			}
		}
	}
	//cv links
	n = collections[0]->links.size();
	stream << n << std::endl;
	for (auto c : collections[0]->links)
	{
		stream << c.fromComponent << " " << c.from->name << " ";
		stream << c.toComponent << " " << c.to->name << " " << c.amount << " \n";
	}
	//raw parameters
	n = 0;
	for (auto c : collections[0]->components)
	{
		n += c.second->parameters.size();
	}
	stream << n << std::endl;
	for (auto c : collections[0]->components)
	{
		for (auto d : c.second->parameters)
		{
			stream << c.second->name << " " << d.first << " " << d.second->getBaseValue() << "\n";
		}
	}
}

void Synth::playNoteDuration(Note note, float seconds)
{
	noteDown(note);
	noteUpTimer[(int)note.note] = seconds;
}

std::vector<std::string>* Synth::getComponentList()
{
	componentList.clear();
	for (auto c : collections[0]->components)
	{
		componentList.push_back((c.second)->name);
	}
	return &componentList;
}

std::vector<std::string> Synth::getComponentTypesList()
{
	return ComponentFactory::getTypesList();
}