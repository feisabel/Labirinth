#ifndef __BLOCK
#define __BLOCK

#include "entity.h"

class Block : public Entity
{
protected:	
	enum Type {FLOOR, WALL} _type; 	// Se FLOOR então é caminho e WALL é parede.
	bool lit;	 					// Define se o bloco consta no FOV(field of vision) do player ou não.

public:
	Block() : _type(WALL), lit(false) {}
	
	Type& type() { return _type; }
	Type type() const { caminho = a; }

	bool is_lit() { return lit; }
	void enlighten() { lit = true; }
};


#endif