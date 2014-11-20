#ifndef __CONTINUE
#define __CONTINUE

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "scene.h"
#include "menu.h"

class Main;

class MenuContinue : public Scene
{
public:
    void redraw();
    void update();
    MenuContinue();

private:
    Button button[3];
    sf::RectangleShape title_teste;
    sf::Text title;
    sf::Font font;
};

#endif
