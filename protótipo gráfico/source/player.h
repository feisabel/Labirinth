#ifndef __PLAYER
#define __PLAYER

#include "item.h"
#include "character.h"
#include <SFML/System/Clock.hpp>

class Player : public Character
{
	static const int max_ammo = 30;
	static const int max_hp = 10;

	static const unsigned fov = 4;

	sf::Clock clock;
	sf::Time _start;
	sf::Time _end;
	int _ammo;
	int _points;
	Direction _direction;

public:
	Player() : _ammo(max_ammo), _points(0) {}

	void start(){ _start = clock.getElapsedTime(); }
	void end(){ _end = clock.getElapsedTime(); }
	void get(Item i)
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
    int points() const { return _points; }
	Direction direction() const { return _direction; }
	Direction& direction() { return _direction; }

	bool in_fov(const Entity& e)
	{
		return _pos.x-4 <= e.x() && e.x() <= _pos.x+4 && _pos.y-4 <= e.y() && e.y() <= _pos.y+4;
	}
    int count_points()
    {
        _points = _ammo*10 + _hp*30 + 300/(_end.asSeconds()-_start.asSeconds());
        return _points;
    }
};


#endif
