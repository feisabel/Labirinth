#ifndef __ITEM
#define __ITEM

#include "entity.h"
#include "random.h"

class Item : public Entity
{
public:
	enum Type {HEAL, AMMO};
protected:
	int _amount;
	Type _type; //true -> heart, false -> ammo

public:
	Item() { _amount = randomize(5, 10); }
	Item(Type t) : _type(t) { _amount = randomize(5, 10); }
	Item(Type t, int a) : _amount(a), _type(t) {}

	int& amount() { return _amount; }
	int amount() const { return _amount; }
	Type& type() { return _type; }
	Type type() const { return _type; }
};

#endif
