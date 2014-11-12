#ifndef __GAME
#define __GAME

#include "custom/list.h"
using custom::list;

#include "player.h"
#include "maze.h"
#include "spawn.h"
#include "trap.h"
#include "item.h"

class Game
{
private:
	Maze maze;
	Player player;
	list<Item> ammuns;    // A definir.
	list<Item> hearts;
	list<Trap> traps;
	list<Spawn> spawns;

public:	
	Game();

	void loop(); // Onde o jogo acontece.
	void update();
	
	void init();
};

#endif