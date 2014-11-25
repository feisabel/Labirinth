#ifndef __ENEMY
#define __ENEMY

#include "character.h"
#include "player.h"
#include "maze.h"
#include "timer.h"

#include "custom/queue.h"
using custom::queue;


/*
	classe Enemy:
		Representa um inimigo. Se estiver no campo de visão do jogador,
		altera seu estado da seguinte forma:
			se estiver no estado SLEEP, passa por estado AWAKE
			se estiver no estado AWAKE, começa a perseguir o jogador
*/

class Enemy : public Character
{
public:
	enum State { AWAKE, SLEEP };

	// construtores
	Enemy();		// construtor padrão
	Enemy(State s); // construtor com um State

	// getter/setter
	Direction& direction();		 // retorna a direção do inimigo
	Direction direction() const; // retorna a direção do inimigo (const)

	void init_awake();			 // inicia a troca de SLEEP pra AWAKE
	bool inited_awake() const;   // se já iniciou a troca

	void awake();				 // troca de estado pra AWAKE
	bool is_awake() const;		 // se o estado é AWAKE

	void init_chase();			
	bool is_chasing() const;

	bool hit_player();
    bool hit_bullet();

	// perseguição
	bool trace_route(Player&, Maze&);
	bool chase(Player&, Maze&, queue<Position>&);

private:
	State state;

	queue<Position> route;

	Direction dir;

	bool chasing;
	bool hit_p;
    bool hit_b;
	bool set_awake;
};


#endif