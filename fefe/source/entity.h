#ifndef __ENTITY
#define __ENTITY

#include "position.h"

class Entity
{
protected:
	Position _pos;

public:
	Entity() : _pos(0,0) {}
	Entity(int a, int b) : _pos(a, b) {}
	
	int& x() { return _pos.x; }
	int& y() { return _pos.y; }
	
	int x() const { return _pos.x; }
	int y() const { return _pos.y; }

	Position& pos() { return _pos; }
	const Position& pos() const { return _pos; }

	bool collided_with(const Entity& e) const
	{
		return _pos == e._pos;
	}
    
    bool collided_with(const Position& e) const
    {
        return _pos == e;
    }
};

#endif