#ifndef __SPAWN
#define __SPAWN

#include "custom/list.h"
using custom::list;

#include "entity.h"
#include "enemy.h"


class Spawn : public Entity
{
	list<Enemy*> children;

public:
	Spawn() {}
	
	~Spawn();
	
	Enemy* create_enemy();
	void destroy_enemy(Enemy* e);

	void update();
};


#endif