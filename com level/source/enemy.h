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

	void init_chase();			 // inicia a perseguição do player
	bool is_chasing() const;     // indica estado de perseguição ou de inatividade

	bool hit_player() const;      // indica se o inimigo está atacando o player no loop atual
    bool hit_bullet() const;      // indica se o inimigo foi atingido por um tiro no loop atual

	// perseguição
	bool trace_route(Player&, Maze&);             // traça a rota de perseguição a ser tomada pelo inimigo para alcançar o jogador
	bool chase(Player&, Maze&, queue<Position>&); // a função que faz com que o inimigo persiga o jogador

private:
	State state; 	  		// define o estado atual do inimigo (SLEEP ou AWAKE)

	queue<Position> route;  // define em qual posição da rota (caso esteja em perseguição) o inimigo se encontra

	Direction dir;          // final da rota

	bool chasing;           // define se está ou não em perseguição
	bool hit_p;             // variável booleana que define se está atacando o player ou não
    bool hit_b;             // variável booleana que define se levou um tiro ou não
	bool set_awake;         // define que está AWAKE ou SLEEP
};


#endif