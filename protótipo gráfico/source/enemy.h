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
public:
	enum State { AWAKE, SLEEP };

private:
	State state;

	queue<Position> route;

	bool chasing;
	bool hit;
	bool set_awake;

public:
	Enemy() : state(AWAKE), set_awake(false), chasing(false), hit(false) {}
	Enemy(State s) : state(s), set_awake(false), chasing(false), hit(false) {}

	void init_awake() { set_awake = true; }
	bool inited_awake() { return set_awake; }

	void awake() { if (set_awake) state = AWAKE; }
	bool is_awake() { return state == AWAKE; }

	void init_chase();
	bool is_chasing();

	bool trace_route(Player&, Maze&);
	bool chase(Player&, Maze&);

	bool hit_player();
};


#endif