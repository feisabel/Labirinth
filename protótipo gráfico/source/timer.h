#ifndef __TIMER
#define __TIMER

#include <ctime>


class Timer
{
    unsigned long long counter;
    unsigned long long max;

public:
    Timer(double usec) : counter(usec * CLOCKS_PER_SEC / 1000000) {}
    
    bool tick()
    {
    	if (counter > 0)
        {
            --counter;
            return true;
        }
    	else return false;
    }
    
    bool ended() { return counter == 0; }

    void reboot() { counter = max; }

    unsigned long long remaining() const { return counter; }
};


#endif
