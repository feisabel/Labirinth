#ifndef __PLAYER
#define __PLAYER

#include "item.h"
#include "character.h"

class Player : public Character
{
	static const int max_ammn = 30;
    
public:
	Player(): _ammun(max_ammn) {}

	bool get(Item i);	
	int ammunition() const { return _ammun; }

    char direction () const { return _direction; }
    void direction (char d) { _direction = d; }

private:	
	int _ammun;
    char _direction;
};


#endif