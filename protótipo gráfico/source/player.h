#ifndef __PLAYER
#define __PLAYER

#include "item.h"
#include "character.h"

class Player : public Character
{
	static const int max_ammo = 30;
public:
	Player(): _ammo(max_ammo) {}

	void mark_path();
	void shoot();
	bool get(Item i);
	void change_ammo(int a) { for(; _ammo < max_ammo && a != 0; _ammo++, a--); }
	int ammo() const { return _ammo; }
	char direction() const { return _direction; }
	void direction(char d) { _direction = d; }

private:
	int _ammo;
	char _direction;
};


#endif
