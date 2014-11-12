#ifndef __ENEMY
#define __ENEMY

#include "character.h"
#include "player.h"

class Enemy : public Character
{
public:
	bool chase(Player&);
};


#endif