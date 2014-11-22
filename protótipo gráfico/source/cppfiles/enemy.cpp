#include "../enemy.h"
#include "../maze.h"

#include "../custom/queue.h"
using custom::queue;

#include "../custom/stack.h"
using custom::stack;


bool Enemy::trace_route(Player& player, Maze& maze)
{
	stack<Position> result;

	queue<Position> bfs;
	bfs.push(_pos);
	while (!bfs.empty() && bfs.front() != player.pos())
	{	
		list<Position> tmp = get_adjacents(bfs.front());

		while (!tmp.empty())
		{	
			Position p = tmp.pop_front();
			if (maze.in_bounds(p) && maze[p.x][p.y].type() != Block::WALL && !result.includes(p))
				bfs.push(p);
		}

		result.push(bfs.pop());
	}
	
	if (!bfs.empty())
	{
		stack<Position> path;
		path.push(bfs.pop());
		while (!result.empty())
		{
			Position x = result.pop();
			if (x.is_adjacent_to(path.top()))
			{
				path.push(x);
			}
		}

		path.pop();

		while (!path.empty())
		{
			route.push(path.pop());
		}

		return true;
	}
	else return false;
}


void Enemy::init_chase()
{
	chasing = true;
}

bool Enemy::chase(Player& player, Maze& maze)
{	
	if (chasing)
	{
		if (collided_with(player))
		{
			route.clear();
			chasing = false;
			return false;
		}
		else if (route.empty())
		{
			bool found_route = trace_route(player, maze);
			if (!found_route) return false;
		}
		 
		_pos = route.pop();
		
		return true;
	}
	return false;
}


bool Enemy::is_chasing()
{
	return chasing;
}