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
}