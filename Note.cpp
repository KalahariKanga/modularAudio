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


Note::~Note()
{
}
