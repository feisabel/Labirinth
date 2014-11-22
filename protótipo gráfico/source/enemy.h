#ifndef __ENEMY
#define __ENEMY

#include "character.h"
#include "player.h"
#include "maze.h"

#include "custom/queue.h"
using custom::queue;


class Enemy : public Character
{
	queue<Position> route;
	bool chasing;

public:
	Enemy() : chasing(false) {}

	void init_chase();
	bool trace_route(Player&, Maze&);
	bool chase(Player&, Maze&);
	bool is_chasing();
};


#endif