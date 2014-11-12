#include "../enemy.h"

#include "custom/queue.h"
using custom::queue;


void Enemy::chase(Player& player)
{
	if (pos == player.pos)
	{
		return; 
	}
	else
	{
		queue<Position> path;
		Position next = pos;
		do
		{	
			path.push(next);
			
			get_adjacents(path.top()).for_each
			(
				[&path] (Position& p)
				{
					path.push(p);
				}
			);
		}
		while (!path.is_empty() && path.top() != player.pos);
	}
}