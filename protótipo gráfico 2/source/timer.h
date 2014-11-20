#ifndef __timer__
#define __timer__

#include <ctime>


class Timer
{
    unsigned long long cont, max;

public:
    Timer(double usec) : cont(0), max(usec * CLOCKS_PER_SEC / 1000000) {}
    
    bool tick()
    {
    	cont++;
    	if (cont < max) return true;
    	else return false;
    }
    
    void reboot() { cont = 0; }
    unsigned long long time_remaining() const { return max - cont; }
};

#endif
