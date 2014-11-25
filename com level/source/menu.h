#ifndef __MENU
#define __MENU

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "scene.h"
#include "timer.h"

class Main;


// classe cena do menu principal
class Menu : public Scene
{
public:
    void redraw(); //método que redesenha as atualizações
    void update(); //método que pega os eventos e trata devidamente
    Menu(); //construtor padrão
private:

    sf::Texture background;
    sf::Sprite spriteBackground;
};

#endif
