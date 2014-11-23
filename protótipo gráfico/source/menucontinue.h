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
    sf::Texture exit;
    sf::Texture resume;
    sf::Texture menu;
    sf::Texture restart;

    sf::Sprite spriteExit;
    sf::Sprite spriteResume;
    sf::Sprite spriteMenu;
    sf::Sprite spriteRestart;

    sf::RectangleShape rect;
    sf::Text title;
    sf::Font font;
};

#endif
