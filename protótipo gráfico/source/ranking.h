#ifndef _RANKING
#define _RANKING

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "scene.h"
#include "custom/list.h"

using custom::list;

struct players
{
    std::string name;
    int points;
};

class Ranking : public Scene
{
public:
    void redraw();
    void update();
    void refresh();
    void read_from_file();
    Ranking();
private:
    list<players> myRanking;
    sf::Texture background;
    sf::Sprite spriteBackground;
    sf::Font font;
    sf::Text text;
};


#endif
