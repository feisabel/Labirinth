#include "../random.h"

int randomize (int i, int j)
{
	static bool inited = false;
	if (!inited)
    {
		srand(time(NULL));
		inited = true;
	}

	return i + rand()%(j-i+1);
}