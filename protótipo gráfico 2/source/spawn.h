#ifndef __SPAWN
#define __SPAWN

#include "entity.h"
#include "enemy.h"


class Spawn : public Entity
{
private:
	list<Enemy*> children;

public:
	Spawn() {}

	Enemy* const create_enemy() { children.push_back(new Enemy); return children.back(); }
	void destroy_enemy() { delete children.pop_back(); }
};

#endif