#ifndef __ITEM
#define __ITEM

#include "entity.h"

class Item : public Entity
{
protected:
	int _amount;

public:
	Item() : _amount(0) {}
	Item(int a) : _amount(a) {} 

	int& amount() { return _amount; }
	int amount() const { return _amount; }
};

#endif