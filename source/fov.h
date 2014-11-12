#ifndef __FOV
#define __FOV

class FOV
{
	int _radius;
public:
	FOV(): _radius(0) {}

	int& radius() { return campo_visao; }
	int radius() const { return campo_visao; }
};

#endif