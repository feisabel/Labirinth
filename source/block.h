#ifndef __BLOCK
#define __BLOCK

#include "entity.h"

class Block : public Entity
{
public:
	enum Type {FLOOR, WALL}; 				
	
	Block() : _type(WALL), lit(false) {}
	
	Type& type() { return _type; }
	Type type() const { return _type; }

	bool is_lit() { return lit; }
	void enlighten() { lit = true; }

protected:	
	Type _type; 	// Se FLOOR então é caminho, se WALL é parede.
	bool lit;	 	// Define se o bloco consta no FOV(field of vision) do player ou não.
};


#endif