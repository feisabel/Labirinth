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
	
	bool chasing;
	bool hit_p;
    bool hit_b;

public:
	Enemy() : chasing(false), hit_p(false), hit_b(false) {}

	void init_chase();
	bool trace_route(Player&, Maze&);
	bool chase(Player&, Maze&);
	bool is_chasing();
	bool hit_player();
    bool hit_bullet();
};


#endif