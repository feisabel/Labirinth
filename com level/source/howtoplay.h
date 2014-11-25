#ifndef __HOWTOPLAY
#define __HOWTOPLAY

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "scene.h"
#include "timer.h"

class Main;

// classe cena do how to play
class howToPlay : public Scene
{
    public:
    void redraw(); // método que mostra as modificações
    void update(); // método que recebe eventos e faz modificações
    howToPlay(); //construtor padrão
private:

    sf::Texture background;  
    sf::Sprite spriteBackground; 

};

#endif
