#include "../position.h"

list<Position> get_adjacents(const Position& p)
{
	list<Position> tmp;

	int deltaX[4] = {-1, 0, 1, 0};
	int deltaY[4] = { 0, 1, 0,-1};

	for (int i=0; i<4; i++)
	{
		tmp.push_back(Position(p.x + deltaX[i], p.y + deltaY[i]));
	}

	return tmp;
}


Position get_adjacent(const Position& p, const Direction& d)
{
	    if(d == UP)
            return Position(p.x, p.y-1);
		if(d == DOWN)
            return Position(p.x, p.y+1);
		if(d == LEFT)
            return Position(p.x-1, p.y);
		if(d == RIGHT)
            return Position(p.x+1, p.y);

}


std::ostream& operator<< (std::ostream& out, const Position& p)
{
	return out << "(" << p.x << ", " << p.y << ")";
}

std::istream& operator>> (std::istream& in, Position& p)
{
	return in >> p.x >> p.y;
}

