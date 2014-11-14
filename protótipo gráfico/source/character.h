#ifndef __CHARACTER
#define __CHARACTER

#include "entity.h"

class Character : public Entity
{
protected:	
	int _hp;
	int _vel;

public:
	Character(): _hp(0), _vel(0) {}
	
	void move_to(Position& p) { _pos = p; } 
	void receive_dmg(int dmg);
	
	int hp() const { return _hp; }
	int vel() const { return _vel; }

	int& hp() { return _hp; }
	int& vel() { return _vel; }
};


#endif