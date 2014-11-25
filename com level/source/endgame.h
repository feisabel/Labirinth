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
    void redraw(); //redesenha as atualizações na tela
    void update(); //recebe eventos e faz as mudanças necessárias

    EndGame(); //construtor padrão

    void add_ranking(); //método que adiciona nome e pontos ao ranking.txt
    void points(int a) //recebe um inteiro; altera a string _points
    {
        std::stringstream ss;
        ss << a;
        _points = ss.str();
    }
    std::string str; //nome do player
    std::string _points; //pontos do player no jogo atual
    sf::RectangleShape rect;
    sf::Text text1;
    sf::Text text2;
    sf::Text text3;
    sf::Text text4;
    sf::Text text5;
    sf::Font font;

};


#endif
