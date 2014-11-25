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
#include "enemy.h"
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
	int level; //Qual o level atual do jogo
	Maze maze; //Labirinto usado no jogo
	Player player; //Declaração do player
	list<Item> ammuns; //Lista de munições que estão espalhadas pelo labirinto
	list<Item> hearts; //Lista de vidas, que são convertidas em hp, que estão espalhadas pelo labirinto
	list<Trap> traps; //Lista de armadilhas espalhadas pelo labirinto
	list<Enemy> enemies; //Lista de inimigos 
    queue<Position> bullet_course; //Lista com as posições das balas quando atiradas

    bool inited;

    sf::Music music; //Declaração de música usando a biblioteca gráfica
    bool playing; //Booleano que indica se o há som ou se está mudo

    sf::SoundBuffer gunfire; //Som do tiro 
    sf::SoundBuffer bufferZombieAwake; 
    sf::SoundBuffer bufferZombieDead;
    sf::SoundBuffer bufferPlayerDmg; 

    sf::Sound soundGunfire;
    sf::Sound zombie_awake;
    sf::Sound zombie_dead;
    sf::Sound player_dmg;

    sf::Texture cross; //Textura do x
    sf::Texture map; //Textura do pergaminho
    sf::Texture h1, h2, h3, h4, h5; //Textura dos corações que aparecem com as vidas
    sf::Texture musicplayON; //Símbolo que indica som tocando
    sf::Texture musicplayOFF; //Símbolo que indica mudo
    sf::Texture exit; //Textura da saída
	sf::Texture floor; //Textura do chão
	sf::Texture trap_off; //Textura da armadilha desativada
	sf::Texture trap_on;  //Textura da armadilha ativada
	sf::Texture spawn; //Textura do spaw
	sf::Texture monster_front; //Textura do inimigo
    sf::Texture monster_back; //Textura do inimigo
    sf::Texture monster_left; //Textura do inimigo
    sf::Texture monster_right; //Textura do inimigo
	sf::Texture ammo; //Textura da munição
	sf::Texture med; //Textura do medkit
	sf::Texture character_back; //Textura do player
	sf::Texture character_front; //Textura do player
	sf::Texture character_left; //Textura do player
	sf::Texture character_right; //Textura do player
    sf::Texture bullet_up; //Textura da bala
    sf::Texture bullet_down; //Textura da bala
    sf::Texture bullet_left; //Textura da bala
    sf::Texture bullet_right; //Textura da bala
    sf::Texture wall_left; //Textura da parede
    sf::Texture wall_left_right; //Textura da parede
    sf::Texture wall_left_up; //Textura da parede
    sf::Texture wall_left_down; //Textura da parede
    sf::Texture wall_left_right_up; //Textura da parede
    sf::Texture wall_left_right_down; //Textura da parede
    sf::Texture wall_down; //Textura da parede
    sf::Texture wall_full; //Textura da parede
    sf::Texture wall_unlit; //Textura da parede
    sf::Texture wall_up; //Textura da parede
    sf::Texture wall_up_down; //Textura da parede
    sf::Texture wall_right; //Textura da parede
    sf::Texture wall_right_up; //Textura da parede
    sf::Texture wall_right_down; //Textura da parede
    sf::Texture wall_left_up_down; //Textura da parede
    sf::Texture wall_right_up_down; //Textura da parede
    sf::Texture fade_out; //Textura que escurece as extremidades da tela

    //Declaração dos sprites que são desenhados na cena Game
    sf::Sprite spriteCross; 
    sf::Sprite spriteMap;
    sf::Sprite spriteAmmoToSee;
    sf::Sprite spriteHeart;
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
    sf::Sprite spriteFadeOut;

    sf::Font font; //Declaração da fonte usada

    sf::Text player_hp; //Texto usado para mostrar a quantidade de hp
    sf::Text player_ammo; //Texto usado para mostrar a quantidade de munição
    sf::Text player_level; //Texto usado para mostrar o level

    sf::CircleShape circle; //Declaração do círculo que indica a posição relativa do personagem no labirinto

    Timer timer; 

	Game();

	void update(); //Recebe eventos e trata devidamente
	void redraw(); //Desenha as mudanças na tela

    void restart(); //Método que reinicia o jogo
    void active_traps(); //Método que ativa ou desativa as armadilhas

    void useAmount(); //Método que tira um item da lista de itens
    void fire(); //Método que atira

    void define_wall(int, int);

    bool showSpawn(int, int); //Retorna verdadeiro caso na posição i, j haja Spawn
    bool showMonster(int, int); //Retorna verdadeiro caso na posição i, j haja monstro
	bool showAmmo(int, int); //Retorna verdadeiro caso na posição i, j haja munição
	bool showMed(int, int); //Retorna verdadeiro caso na posição i, j haja medkit
	bool showTrap(int, int); //Retorna verdadeiro caso na posição i, j haja armadilha

    bool read_from_file(int); //Método que lê as informações do arquivo de entrada e atualiza as instâncias do game
	bool verify_maze(Maze&); //Método que verifica a validade de um labirinto
    void changeLevel(int); //Método que faz a mudança de level

    void playMusic(bool a) //Método que ativa ou desativa o som do jogo
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
    int xX, yY; //Coordenadas do ponto vermelho que fica no mini mapa de orientação
    void changeXY(); //Função que altera as coordenadas do ponto vermelho conforme a mudança de posição do player
};

#endif
