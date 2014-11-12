#include "lista.h"
#include "lista.hpp"
#include <cstdlib>

int randomize (int i, int j)
{
	return i + rand()%(j-i+1);
}

struct Position
{
	int x;
	int y;
	Position (): x(0), y(0) {}
	Position (int a, int b): x(a), y(b) {}

	bool operator== (const Position& other)
	{
		return other.x == x && other.y == y;
	}
};


class Entity
{
protected:
	Position pos;

public:
	Entity(): pos(0,0) {}
	Entity(int a, int b): pos(a, b) {}
	
	int& x() { return pos.x; }
	int& y() { return pos.y; }
	
	int x() { return pos.x; } const;
	int y() { return pos.y; } const;

	bool collided_with(const Entity& e) const;
	{
		return pos == e.pos;
	}
};


class Item : public Entity
{
protected:
	int _amount;

public:
	item(): _amount(0) {}
	item(int a): _amount(a) {} 

	int& amount() { return _amount; }
	int amount() const { return _amount; }
};


class Block : public Entity
{
protected:	
	enum Type {FLOOR, WALL} _type; 	// Se FLOOR então é caminho e WALL é parede.
	bool lit;	 					// Define se o bloco consta no FOV(field of vision) do player ou não.

public:
	Block(): _type(WALL), lit(false){}
	
	Type& type() { return _type; }
	Type type() const { caminho = a; }

	bool is_lit() { return lit; }
	void enlighten() { lit = true; }
};

class Trap : public Entity
{
private:
	bool activated;

public:
	Trap(): activated(false) {}

	bool is_active() { return activated; }
	void activate() { activated = true; }
};


class Character : public Entity {
protected:	
	int _hp;
	int _vel;

public:
	Character(): _hp(0), _vel(0) {}
	
	void move(); 
	void receive_dmg()();
	
	int hp() const { return _hp; }
	int vel() const { return _vel; }

	int& hp() { return _hp; }
	int& vel() { return _vel; }
};

class Player : public Character
{
private:	
	int _ammun;

public:
	Player(): _ammun( 0 ) {}
	void mark_path();
	void shoot();
	bool get(Item i);
	int ammunition() const { _ammun = a; }
};


class Enemy : public Character
{
public:
	bool chase(Player&);
};


class FOV
{
	int _radius;
public:
	FOV(): _radius(0) {}

	int& radius() { return campo_visao; }
	int radius() const { return campo_visao; }

	bool update();
};


class Maze
{
	struct Proxy 
	{
		Block* vector;

		Proxy(int n)
		{
			vector = new Block[n];
		}

		~Proxy()
		{
			delete vector;
		}

		Block& operator[] (int i)
		{
			return vector[i];
		}

		const Block& operator[] (int i) const
		{
			return vector[i];
		}
	};


	int lin;
	int col;

public:
	Proxy *matrix;

	Position _entrance;
	Position _exit;

	Maze(int n, int m)
	: lin(n), col(m)
	{
		matrix = new Proxy[n](m);
	}

	~Maze()
	{
		delete matrix;
	}

	Position entrance(int a, int b) { entrance.x = a; entrance.y = b; }
	Position exit(int a, int b) { saida.x = a; saida.y = b; }

	Proxy& operator[] (int idx) { return matrix[idx]; }
	const Proxy& operator[] (int idx) const { return matrix[idx]; }
};


class Spawn
{
	list<Enemy*> children;

public:
	Spawn() {}
	
	~Spawn()
	{
		while (!children.is_empty())
		{
			delete children.pop_front();
		}
	}
	
	Enemy* create_enemy() { children.push_back(new Enemy); return *children.back() }
	void destroy_enemy(Enemy* e) { children.remove(children.find(&e)); }

	void update() { children.for_each() }
};


class Game
{
private:
	Maze maze;
	Player player;
	list<Enemy> enemies; // A definir.
	list<Item> ammuns;    // A definir.
	list<Item> hearts;
	list<Trap> traps;
	list<Spawn> spawns;

public:	
	Game()
	{
		load_from_file();	
	}

	
	void loop(); // Onde o jogo acontece.
	void update();
	
	void init();
};

// Função que forma o labririnto conforme as informações do arquivo de entrada e modifica entrance e exit
void Game::init()
{
	int i, j;
	cena.setDimencoes( dimen.x, dimen.y );
	cena.matriz = new bloco*[cena.dimencoes.x];
	for( i = 0; i < cena.dimencoes.x; i++ )
		cena.matriz[i] = new bloco[cena.dimencoes.y];
	for( i = 0; i < cena.dimencoes.x; i++ ){
		for( j = 0; j < cena.dimencoes.y; j++ ){
			if( arquivo[i][j] != 1 )
				cena.matriz[i][j].setCaminho(true);
			if( arquivo[i][j] == 2 )
				cena.setentrance(i, j);	
			if( arquivo[i][j] == 3 )
				cena.setSaida(i, j);
			if( arquivo[i][j] == 4 ){
				Trap nova;
				nova.setX(i);
				nova.setY(j);
				lista_Trap.push(nova);
			}
			if( arquivo[i][j] == 5 ){
				Enemy novo;
				novo.setX(i);
				novo.setY(j);
				lista_spawn.push(novo);
			}
			if( arquivo[i][j] == 6 ){
				item vida(randomica(2, 4));
				lista_vida.push(vida);    // A quantidade é gerada randomicamente.
			}
			if( arquivo[i][j] == 7 ){
				item muni(randomica(6, 18));
				lista__ammun.push(muni); // A quantidade é gerada randomicamente.
			}
			if( arquivo[i][j] == 8 ){
				Enemy novo;
				novo.setX(i);
				novo.setY(j);
				lista_Enemy.push(novo);
			}
		} 
	}	
}

