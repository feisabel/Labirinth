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
    queue<Position> bullet_course;


	sf::Texture wall;
	sf::Texture floor;
	sf::Texture monster_front;
	sf::Texture character_back;
	sf::Texture character_front;
	sf::Texture character_left;
	sf::Texture character_right;
    sf::Texture bullet_up;
    sf::Texture bullet_down;
    sf::Texture bullet_left;
    sf::Texture bullet_right;


	sf::Sprite spriteWall;
	sf::Sprite spriteFloor;
	sf::Sprite spriteMonster;
	sf::Sprite spriteCharacter;
    sf::Sprite spriteBullet;

	Game();

	void update();
	void redraw();

    bool showMonster(int, int);
	bool read_from_file();
    void fire();
};

#endif