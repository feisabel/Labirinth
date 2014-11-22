#ifndef __ENEMY
#define __ENEMY

#include "character.h"
#include "player.h"
#include "maze.h"
#include "timer.h"

#include "custom/queue.h"
using custom::queue;


class Enemy : public Character
{
	queue<Position> route;
	
	Timer sleep;
	bool chasing;

public:
	Enemy() : sleep(2000000), chasing(false) { sleep.end(); }

	void init_chase();
	bool trace_route(Player&, Maze&);
	bool chase(Player&, Maze&);
	bool is_chasing();
};


#endif