#ifndef __ITEM
#define __ITEM

#include "entity.h"

class Item : public Entity
{
protected:
	size_t _amount;

public:
	enum Type {HEALTH, AMMUN} _type;

	Item() : _amount(0) {}
	Item(size_t a) : _amount(a) {} 

	Type& type() { return _type; }
	Type type() const { return _type; }

	size_t& amount() { return _amount; }
	size_t amount() const { return _amount; }
};

#endif