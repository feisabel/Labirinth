#ifndef __PLAYER
#define __PLAYER

#include "character.h"

class Player : public Character
{
	static const int max_ammn = 30;
public:
	Player(): _ammun(max_ammn) {}

	void mark_path();
	void shoot();
	bool get(Item i);
	int ammunition() const { return _ammun; }

private:	
	int _ammun;
};


#endif