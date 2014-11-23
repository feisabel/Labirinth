#ifndef __TIMER
#define __TIMER

#include <SFML/System/Clock.hpp>

class Timer
{
    sf::Clock clock;
    sf::Int64 limit;

public:
    Timer(sf::Int64 usec) : limit(usec) {}
    
    bool tick()
    {
    	if (clock.getElapsedTime().asMicroseconds() >= limit)
        {
            clock.restart();
            return true;
        }
    	else return false;
    }
    
    bool ended() const { return clock.getElapsedTime().asMicroseconds() >= limit; }

    void reboot() { clock.restart(); }

    sf::Int64 remaining() const { return clock.getElapsedTime().asMicroseconds(); }
};


#endif
