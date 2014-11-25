#ifndef __TIMER
#define __TIMER

#include <SFML/System/Clock.hpp>

//Classe que regula o tempo em que precisa fazer o update
class Timer
{
    sf::Clock clock;
    sf::Int64 limit;

public:
    Timer(sf::Int64 usec) : limit(usec) {}
    
    bool tick() //verifica se já atingiu o tempo máximo
    {
    	if (clock.getElapsedTime().asMicroseconds() >= limit) 
        {
            clock.restart(); //reinicia
            return true;
        }
    	else return false;
    }
    
    //retorna verdadeiro caso o tempo atual esteja maior ou igual ao limite
    bool ended() const { return clock.getElapsedTime().asMicroseconds() >= limit; }

    //reinicia o clock
    void reboot() { clock.restart(); }

    sf::Int64 remaining() const { return clock.getElapsedTime().asMicroseconds(); }
};


#endif
