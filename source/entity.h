#ifndef __ENTITY
#define __ENTITY

#include "position.h"

class Entity
{
protected:
	Position pos;

public:
	Entity() : pos(0,0) {}
	Entity(int a, int b) : pos(a, b) {}
	
	int& x() { return pos.x; }
	int& y() { return pos.y; }
	
	int x() { return pos.x; } const;
	int y() { return pos.y; } const;

	bool collided_with(const Entity& e) const;
	{
		return pos == e.pos;
	}
};

#endif