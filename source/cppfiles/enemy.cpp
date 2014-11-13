#include "../enemy.h"
#include "../maze.h"

#include "../custom/queue.h"
using custom::queue;

#include "../custom/stack.h"
using custom::stack;

#include <iostream>

bool Enemy::chase(Player& player, Maze& m)
{
	if (collided_with(player))
	{
		return true; 
	}
	else
	{
		stack<Position> result;

		queue<Position> bfs;
		bfs.push(_pos);
		while (!bfs.is_empty() && bfs.front() != player.pos())
		{	
			list<Position> tmp = get_adjacents(bfs.front());

			while (!tmp.is_empty())
			{	
				Position p = tmp.pop_front();
				if (m[p.x][p.y].type() != Block::WALL)
					bfs.push(p);
			}

			result.push(bfs.pop());
		}
		
		if (!bfs.is_empty())
		{
			stack<Position> path;
			path.push(bfs.pop());
			while (!result.is_empty())
			{
				Position x = result.pop();
				if (x.is_adjacent_to(path.top()))
				{
					path.push(x);
				}
			}

			while (!path.is_empty())
			{	
				Position x = path.pop();
				std::cout << "(" << x.x << ", " << x.y << ")" << std::endl;
			}
			return true;
		}
		else return false;
	}
}