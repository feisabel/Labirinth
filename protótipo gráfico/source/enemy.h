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
	bool hit_p;
    bool hit_b;
	bool set_awake;

public:
	Enemy() : state(AWAKE), set_awake(false), chasing(false), hit_p(false), hit_b(false) {}
	Enemy(State s) : state(s), set_awake(false), chasing(false), hit_p(false), hit_b(false) {}

	void init_awake() { set_awake = true; }
	bool inited_awake() { return set_awake; }

	void awake() { if (set_awake) state = AWAKE; }
	bool is_awake() { return state == AWAKE; }

	void init_chase();
	bool is_chasing();

	bool trace_route(Player&, Maze&);
	bool chase(Player&, Maze&, queue<Position>&);

	bool hit_player();
    bool hit_bullet();
};


#endif