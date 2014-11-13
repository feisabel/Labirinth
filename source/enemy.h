#ifndef __ENEMY
#define __ENEMY

#include "character.h"
#include "player.h"
#include "maze.h"

class Enemy : public Character
{
public:
	bool chase(Player&, Maze&);
};


#endif