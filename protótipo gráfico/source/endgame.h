#ifndef _ENDGAME
#define _ENDGAME

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "scene.h"
#include "menu.h"
#include <SFML/System/String.hpp>

class EndGame : public Scene
{
public:
    void redraw();
    void update();

    EndGame();

    void add_ranking();

    std::string str;
    std::string points;
    sf::RectangleShape rect;
    sf::Text text1;
    sf::Text text2;
    sf::Text text3;
    sf::Text text4;
    sf::Text text5;
    sf::Font font;

};


#endif
