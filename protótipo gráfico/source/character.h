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
<<<<<<< HEAD
	int vel() const { return _vel; }

=======
>>>>>>> dace92ffd2bd9a14bb09c66d3b5b40b9bb650017
	int& hp() { return _hp; }
	int& vel() { return _vel; }
};


#endif