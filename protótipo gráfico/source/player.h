#ifndef __PLAYER
#define __PLAYER

#include "item.h"
#include "character.h"
#include <SFML/System/Clock.hpp>

class Player : public Character
{
public:
	static const int max_ammo = 30;
	static const int max_hp = 10;

private:
	static const unsigned fov = 4;

	sf::Clock clock;
	sf::Time _start;
	sf::Time _end;
	int _ammo;
	int _points;
	Direction _direction;

public:
	Player() : _ammo(max_ammo), _points(0) { _hp = max_hp; }

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
	int& ammo() { return _ammo; }
    void ammo_fire() { _ammo--; }
    int points() const { return _points; }
	
	Direction direction() const { return _direction; }
	Direction& direction() { return _direction; }

	bool can_see(const Entity& e)
	{
		return _pos.x-4 <= e.x() && e.x() <= _pos.x+4 && _pos.y-4 <= e.y() && e.y() <= _pos.y+4;
	}

    void add_points()
    {
        _points+= (_ammo*30 + _hp*50);
    }
};


#endif
