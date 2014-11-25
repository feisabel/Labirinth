#ifndef __BLOCK
#define __BLOCK

#include "entity.h"

//classe Block representa um bloco do labirinto, que pode ser uma parede ou um caminho

class Block : public Entity
{
public:
	enum Type {FLOOR, WALL}; //tipos de bloco: caminho (FLOOR) e parede (WALL)
	
	Block() : _type(WALL) {} //inicializa o bloco como parede
	
	Type& type() { return _type; } //retorna a variável tipo
	Type type() const { return _type; } //retorna o tipo

protected:	
	Type _type; //variável que representa o tipo do bloco
};


#endif