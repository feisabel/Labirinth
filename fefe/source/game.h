#ifndef __GAME
#define __GAME

#include "custom/list.h"
using custom::list;


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>

#include "player.h"
#include "maze.h"
#include "spawn.h"
#include "trap.h"
#include "item.h"
#include "scene.h"
#include "scene_manager.h"
#include "menu.h"
#include "menucontinue.h"
#include "timer.h"

#define FPS 24

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

    sf::Music music;
    bool playing;

    sf::Texture musicplayON;
    sf::Texture musicplayOFF;
    sf::Texture exit;
	sf::Texture floor;
	sf::Texture trap_off;
	sf::Texture trap_on;
	sf::Texture spawn;
	sf::Texture monster_front;
	sf::Texture ammo;
	sf::Texture med;
	sf::Texture character_back;
	sf::Texture character_front;
	sf::Texture character_left;
	sf::Texture character_right;
    sf::Texture bullet_up;
    sf::Texture bullet_down;
    sf::Texture bullet_left;
    sf::Texture bullet_right;
    sf::Texture wall_left;
    sf::Texture wall_left_right;
    sf::Texture wall_left_up;
    sf::Texture wall_left_down;
    sf::Texture wall_left_right_up;
    sf::Texture wall_left_right_down;
    sf::Texture wall_down;
    sf::Texture wall_full;
    sf::Texture wall_unlit;
    sf::Texture wall_up;
    sf::Texture wall_up_down;
    sf::Texture wall_right;
    sf::Texture wall_right_up;
    sf::Texture wall_right_down;
    sf::Texture wall_left_up_down;
    sf::Texture wall_right_up_down;

    sf::Sprite spriteMusic;
	sf::Sprite spriteExit;
	sf::Sprite spriteWall;
	sf::Sprite spriteFloor;
    sf::Sprite spriteTrap;
    sf::Sprite spriteSpawn;
	sf::Sprite spriteMonster;
	sf::Sprite spriteAmmo;
	sf::Sprite spriteMed;
	sf::Sprite spriteCharacter;
    sf::Sprite spriteBullet;

    sf::Font font;

    sf::Text player_hp;

    Timer timer;

	Game();

	void update();
	void redraw();
	void restart();
    void active_traps();
    void useAmount();
    void fire();
    void define_wall(int, int);
    bool showSpawn(int, int);
    bool showMonster(int, int);
	bool showAmmo(int, int);
	bool showMed(int, int);
	bool showTrap(int, int);
	bool read_from_file();
	void playMusic(bool a)
	{
	    if(a){
            music.play();
            playing = true;
	    }
        else{
            music.pause();
            playing = false;
        }
    }
};

#endif