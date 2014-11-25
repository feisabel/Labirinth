#ifndef __CONTINUE
#define __CONTINUE

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "scene.h"
#include "menu.h"

class Main;
//Cena do menu de pausa
class MenuContinue : public Scene
{
public:
    void redraw(); //Método que desenha na tela as modificações
    void update(); //Método que recebe os eventos e faz as modificações necessárias
    MenuContinue();

private:
    sf::Texture exit; //Textura do botão exit
    sf::Texture resume; //Textura do botão resume
    sf::Texture menu; //Textura do botão menu
    sf::Texture restart; //Textura do botão restart

    sf::Sprite spriteExit; //Sprite do botão exit
    sf::Sprite spriteResume; //Sprite do botão resume
    sf::Sprite spriteMenu; //Sprite do botão menu
    sf::Sprite spriteRestart; //Sprite do botão restart

    sf::RectangleShape rect; //Declaração de um retângulo
    sf::Text title; //Texto para o título
    sf::Font font; //Declaração da fonte
};

#endif
