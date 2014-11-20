#ifndef __TRAP
#define __TRAP

#include "entity.h"

class Trap : public Entity
{
private:
	bool activated;

public:
	Trap(): activated(false) {}

	bool is_active() { return activated; }
	void activate() { activated = true; }
	void disactivate() { activated = false; }
};


#endif
