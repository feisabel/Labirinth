#include "../enemy.h"
#include "../maze.h"

#include "../custom/queue.h"
using custom::queue;

#include <iostream>

bool Enemy::chase(Player& player, Maze& m)
{
	if (pos == player.pos)
	{
		return true; 
	}
	else
	{
		stack<Position> result;

		queue<Position> bfs;
		bfs.push(pos)
		while (!bfs.is_empty() && bfs.top() != player.pos)
		{	
			list<Position> tmp = get_adjacents(bfs.top());

			while (!tmp.is_empty())
			{	
				Position p = tmp.pop_front();
				if (maze[p.x][p.y].type != Block::WALL)
					bfs.push();
			}

			result.push(bfs.pop());
		}
		
		if (!bfs.is_empty())
		{
			stack<Position> path;
			path.push(bfs.pop())
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