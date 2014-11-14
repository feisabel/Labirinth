#ifndef __CLASSMAIN
#define __CLASSMAIN
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

const int WINDOW_WIDTH = 560;
const int WINDOW_HEIGHT = 560;

class Main{
public:
    void menu(); //cena do menu (modo pode ser modificado)
    void startGame(sf::RenderWindow* window);  //cena do jogo
    //void credits();
    void howToPlay(sf::RenderWindow* window); //ceno do how to play
};

#endif
