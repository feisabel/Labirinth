#ifndef __CLASSMAIN
#define __CLASSMAIN
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class Main{
    //possivelmente ponteiros de métodos
public:
    void menu();
    void startGame(sf::RenderWindow* window);
    //void credits();
    void howToPlay(sf::RenderWindow* window);
};

#endif
