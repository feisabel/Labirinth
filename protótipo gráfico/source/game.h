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
#include "scene.h"
#include "scene_manager.h"
#include "menu.h"
class Main;

class Game : public Scene
{
public:
	Maze maze;
	Player player;
	list<Item> ammuns;    // A definir.
	list<Item> hearts;
	list<Trap> traps;
	list<Spawn> spawns;
	list<Enemy> enemies;


	sf::Texture wall;
	sf::Texture floor;
	sf::Texture trap_off;
	sf::Texture trap_on;
	sf::Texture monster_front;
	sf::Texture med;
	sf::Texture character_back;
	sf::Texture character_front;
	sf::Texture character_left;
	sf::Texture character_right;


	sf::Sprite spriteWall;
	sf::Sprite spriteFloor;
    sf::Sprite spriteTrap;
	sf::Sprite spriteMonster;
	sf::Sprite spriteMed;
	sf::Sprite spriteCharacter;

	Game();

	void update();
	void redraw();

    //void active_traps();
    bool showMonster(int, int);
	bool showMed(int, int);
	bool showTrap(int, int);
	bool read_from_file();
};

#endif
