#ifndef __GAME
#define __GAME

#include "custom/list.h"
using custom::list;


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "player.h"
#include "maze.h"
#include "spawn.h"
#include "trap.h"
#include "item.h"

class Game
{
public:
	Maze maze;
	Player player;
	list<Item> ammuns;    // A definir.
	list<Item> hearts;
	list<Trap> traps;
	list<Spawn> spawns;
	list<Enemy> enemies;

	Game() {}

	void init(sf::RenderWindow* window);

	bool read_from_file();

	void loop(); // Onde o jogo acontece.
	void update();
};

#endif
