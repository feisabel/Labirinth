#ifndef __POSITION
#define __POSITION

#include "custom/list.h"
using custom::list;

#include <iostream>
#include <cmath>

enum Direction {UP, DOWN, LEFT, RIGHT};

struct Position
{
	int x;
	int y;
	Position () : x(0), y(0) {}
	Position (int a, int b) : x(a), y(b) {}

	bool operator== (const Position& other) const
	{
		return other.x == x && other.y == y;
	}

	bool operator!= (const Position& other) const
	{
		return !operator==(other);
	}

	bool is_adjacent_to (const Position& other) const
	{
		return ( x == other.x && y == other.y + 1 )
			|| ( x == other.x && y == other.y - 1 )
			|| ( y == other.y && x == other.x + 1 )
			|| ( y == other.y && x == other.x - 1 );
	}

	int distance_to(const Position& other) const
	{
		return sqrt(pow((other.x - x), 2) + pow((other.y - y), 2));
	}
};


list<Position> get_adjacents(const Position&);
Position get_adjacent(const Position&, const Direction&);

std::ostream& operator<< (std::ostream&, const Position&);
std::istream& operator>> (std::istream&, Position&);

#endif
