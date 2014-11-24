#ifndef __BLOCK
#define __BLOCK

#include "entity.h"

class Block : public Entity
{
public:
	enum Type {FLOOR, WALL}; 				
	
	Block() : _type(WALL) {}
	
	Type& type() { return _type; }
	Type type() const { return _type; }

protected:	
	Type _type; 	// Se FLOOR então é caminho, se WALL é parede.
};


#endif