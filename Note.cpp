#include "Note.h"

Note::Note()
{

}
Note::Note(Notes n, int v)
{
	note = n;
	frequency = 440 * (pow(pow(2, (double)1 / 12), note - a3));
	velocity = v;
}

Note::Note(sf::Keyboard::Key key, int v)
{
	switch (key)
	{
		case sf::Keyboard::A:
			note = c3;
			break;
		case sf::Keyboard::W:
			note = cs3;
			break;
		case sf::Keyboard::S:
			note = d3;
			break;
		case sf::Keyboard::E:
			note = ds3;
			break;
		case sf::Keyboard::D:
			note = e3;
			break;
		case sf::Keyboard::F:
			note = f3;
			break;
		case sf::Keyboard::T:
			note = fs3;
			break;
		case sf::Keyboard::G:
			note = g3;
			break;
		case sf::Keyboard::Y:
			note = gs3;
			break;
		case sf::Keyboard::H:
			note = a3;
			break;
		case sf::Keyboard::U:
			note = as3;
			break;
		case sf::Keyboard::J:
			note = b3;
			break;
		case sf::Keyboard::K:
			note = c4;
			break;
		default:
			note = NONOTE;
	}
	updateFrequency();
	velocity = v;
}
Note::~Note()
{
}

void Note::updateFrequency()
{
	frequency = 440 * (pow(pow(2, (double)1 / 12), note - a3));
}

