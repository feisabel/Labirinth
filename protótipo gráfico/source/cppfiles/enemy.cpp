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

bool Enemy::hit_player()
{
	return hit;
}

bool Enemy::chase(Player& player, Maze& maze)
{	
	if (chasing)
	{
		if (!route.empty())
		{
			Position old_pos = _pos;
			_pos = route.pop();

			if (collided_with(player))
			{
				route.clear();
				_pos = old_pos;

				player.receive_dmg(1);

				chasing = false;
				hit = true;
			}
		}
		else
		{
			bool found_route = trace_route(player, maze);
			return found_route;
		}
	}

	return chasing;
}


bool Enemy::is_chasing()
{
	return chasing;
}