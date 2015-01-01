#pragma once
class Note
{
public:
	Note();
	Note(int f, int v);
	~Note();
	int frequency;
	int velocity;
};

