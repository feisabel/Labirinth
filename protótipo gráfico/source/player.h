#ifndef __PLAYER
#define __PLAYER

#include "item.h"
#include "character.h"

class Player : public Character
{
	static const int max_ammo = 30;
	static const int max_hp = 10;

	static const unsigned fov = 4;

	int _ammo;
	Direction _direction;

public:
	Player() : _ammo(max_ammo) {}

	bool get(Item i)
	{
		if (i.type() == Item::HEAL)
		{
			_hp += i.amount();
			if (_hp > max_hp) _hp = max_hp;
		}
		else
		{
			_ammo += i.amount();
			if (_ammo > max_ammo) _ammo = max_ammo;
		}
	}

	int ammo() const { return _ammo; }

	Direction direction() const { return _direction; }
	Direction& direction() { return _direction; }

	bool in_fov(const Entity& e)
	{
		return _pos.x-4 <= e.x() && e.x() <= _pos.x+4 && _pos.y-4 <= e.y() && e.y() <= _pos.y+4;
	}
};


#endif
