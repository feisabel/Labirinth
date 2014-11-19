#ifndef __ITEM
#define __ITEM

#include "entity.h"
#include "random.h"

class Item : public Entity
{
protected:
	int _amount;
	int _type; //true -> heart, false -> ammo

public:
	Item() : _type(true) { _amount = randomize(5, 10); }
	Item(bool t) : _type(t) {}
	Item(int a, bool t) : _amount(a), _type(t) {}

	int& amount() { return _amount; }
	int amount() const { return _amount; }
	int& type() { return _type; }
	int type() const { return _type; }
};

#endif
