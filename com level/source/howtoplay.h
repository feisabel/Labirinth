#ifndef __HOWTOPLAY
#define __HOWTOPLAY

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "scene.h"
#include "timer.h"

class Main;

class howToPlay : public Scene
{
    public:
    void redraw();
    void update();
    howToPlay();
private:

    sf::Texture background;  
    sf::Sprite spriteBackground; 

};

#endif
