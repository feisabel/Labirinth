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
	children.push_back(new Enemy);
	return children.back();
}

void Spawn::destroy_enemy(Enemy* e)
{
	children.remove(children.find(&e));
}