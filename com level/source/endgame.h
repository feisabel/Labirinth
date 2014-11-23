#ifndef _ENDGAME
#define _ENDGAME

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <sstream>

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
    void points(int a)
    {
        std::stringstream ss;
        ss << a;
        //std::cout << player.points() <<std::endl;
        _points = ss.str();
    }
    std::string str;
    std::string _points;
    sf::RectangleShape rect;
    sf::Text text1;
    sf::Text text2;
    sf::Text text3;
    sf::Text text4;
    sf::Text text5;
    sf::Font font;

};


#endif
