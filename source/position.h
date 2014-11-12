#ifndef __POSITION
#define __POSITION

#include "custom/list.h"

struct Position
{
	int x;
	int y;
	Position () : x(0), y(0) {}
	Position (int a, int b) : x(a), y(b) {}

	bool operator== (const Position& other)
	{
		return other.x == x && other.y == y;
	}

	bool is_adjacent_to (const Position& other)
	{
		return ( pos.x == other.pos.x && pos.y == other.pos.y + 1 )
			|| ( pos.x == other.pos.x && pos.y == other.pos.y - 1 )
			|| ( pos.y == other.pos.y && pos.x == other.pos.x + 1 )
			|| ( pos.y == other.pos.y && pos.x == other.pos.x - 1 );
	}

	bool operator^ (const Position& other)
	{
		return is_adjacent_to(other);
	}
};


list<Position> get_adjacents(const Position&);

#endif