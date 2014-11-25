#include "../enemy.h"
#include "../maze.h"

#include "../custom/queue.h"
using custom::queue;

#include "../custom/stack.h"
using custom::stack;


Enemy::Enemy()
: state(AWAKE), dir(UP), set_awake(false), chasing(false), hit_p(false), hit_b(false)
{
}


Enemy::Enemy(State s)
: state(s), dir(UP), set_awake(false), chasing(false), hit_p(false), hit_b(false)
{
}

Direction& Enemy::direction()
{
	return dir;
}

Direction Enemy::direction() const
{
	return dir;
}


void Enemy::init_awake()
{
	set_awake = true;
}

bool Enemy::inited_awake() const
{
	return set_awake;
}


void Enemy::awake()
{
	if (set_awake) state = AWAKE;
}

bool Enemy::is_awake() const
{
	return state == AWAKE;
}


void Enemy::init_chase()
{
	chasing = true;
}

bool Enemy::hit_player() const
{
	return hit_p;
}

bool Enemy::hit_bullet() const
{
	return hit_b;
}

bool Enemy::is_chasing()
{
	return chasing;
}


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
			if (x.adjacent_to(path.top()))
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


bool Enemy::chase(Player& player, Maze& maze, queue<Position>& bullet_course)
{
	if (chasing)
	{
		if (!route.empty())
		{
			Position old_pos = _pos;
			_pos = route.pop();
            
			if (_pos == get_adjacent(old_pos, LEFT)) dir = LEFT;
			else if (_pos == get_adjacent(old_pos, RIGHT)) dir = RIGHT;
			else if (_pos == get_adjacent(old_pos, UP)) dir = UP;
			else if (_pos == get_adjacent(old_pos, DOWN)) dir = DOWN;

			if (collided_with(player))
			{
				route.clear();
				_pos = old_pos;
                
				player.receive_dmg(1);
                
				chasing = false;
				hit_p = true;
			}
            else if (!bullet_course.empty() && collided_with(bullet_course.front()))
            {
                route.clear();
                _pos = old_pos;
                
                chasing = false;
                hit_b = true;
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