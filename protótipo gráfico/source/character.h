#ifndef __CHARACTER
#define __CHARACTER

#include "entity.h"

class Character : public Entity
{
protected:
	int _hp;
	int _vel;

public:
	Character(): _hp(5), _vel(0) {}

	void receive_dmg(int dmg) { _hp -= dmg; if (_hp < 0) _hp = 0; }

	int hp() const { return _hp; }
	int vel() const { return _vel; }

	int& hp() { return _hp; }
	int& vel() { return _vel; }
};


#endif
