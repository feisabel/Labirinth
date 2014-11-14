#include "../spawn.h"

Spawn::~Spawn()
{
	while (!children.is_empty())
	{
		delete children.pop_front();
	}
}

Enemy* Spawn::create_enemy()
{
	Enemy* eptr = new Enemy;
	children.push_back(eptr);
	return eptr;
}

void Spawn::destroy_enemy(Enemy* e)
{
	delete e;
}