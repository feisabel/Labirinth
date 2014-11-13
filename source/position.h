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
		return ( x == other.x && y == other.y + 1 )
			|| ( x == other.x && y == other.y - 1 )
			|| ( y == other.y && x == other.x + 1 )
			|| ( y == other.y && x == other.x - 1 );
	}

	bool operator^ (const Position& other)
	{
		return is_adjacent_to(other);
	}
};


list<Position> get_adjacents(const Position&);

#endif