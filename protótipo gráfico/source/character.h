#ifndef __CHARACTER
#define __CHARACTER

#include "entity.h"

class Character : public Entity
{
protected:	
	int _hp;

public:
	Character(): _hp(5) {}
	
	void move_to(Position& p) { _pos = p; }
	void receive_dmg(int dmg) { _hp -= dmg; }
	
	int hp() const { return _hp; }
	int& hp() { return _hp; }
};


#endif