#ifndef __ENTITY
#define __ENTITY

#include "position.h"

/*
	classe Entity:
		Representa as entidades dentro do jogo, individualmente.
*/

class Entity
{
protected:
	Position _pos; // variável com as coordenadas da entidade

public:
	Entity() : _pos(0,0) {}              // construtor da entidade, iniciando as coordenadas em 0, 0
	Entity(int a, int b) : _pos(a, b) {} // construtor da entidade, inciando as coordenadas em a, b
	
	int& x() { return _pos.x; }       // método que retorna a coordenada do eixo x
	int& y() { return _pos.y; }       // método que retorna a coordenada do eixo y
	
	int x() const { return _pos.x; }  // método que retorna a coordenada do eixo x
	int y() const { return _pos.y; }  // método que retorna a coordenada do eixo y

	Position& pos() { return _pos; }             // método que retorna a variável posição atual
	const Position& pos() const { return _pos; } // método que retorna a variável posição atual

	bool collided_with(const Entity& e) const // método que retorna um booleano que define se houve colisão ou não com uma entidade
	{
		return _pos == e._pos;
	}
    
    bool collided_with(const Position& e) const // método que retorna um booleano que define se houve colisão ou não com uma posição
    {
        return _pos == e;
    }
};

#endif