#ifndef _RANKING
#define _RANKING

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "scene.h"
#include "custom/list.h"

using custom::list;

struct players
{
    std::string name;
    int points;
    void add_information(std::string n, int p)
    {
        name = n;
        points = p;
    }
};

struct p
{
    sf::Text name;
    sf::Text points;
    p()
    {
        name.setCharacterSize(20);
        name.setColor(sf::Color::White);
        points.setCharacterSize(20);
        points.setColor(sf::Color::White);
    }

};

class Ranking : public Scene
{
public:
    void redraw();
    void update();
    void read_from_file();
    Ranking();
private:
    p rank[10];
    list<players> myRanking;
    sf::Texture background;
    sf::Sprite spriteBackground;
    sf::Font font;
    sf::Text text;
};

std::string number(int n);
#endif
