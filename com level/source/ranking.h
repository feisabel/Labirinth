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

//Struct players que recebe os dados da leitura do arquivo
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


//Struct p possui nome e pontos para monstrar na tela
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

//Classe da Cena ranking
class Ranking : public Scene
{
public:
    void redraw();
    void update();
    void read_from_file(); //leitura do arquivo ranking.txt
    void refresh(); //atualiza o ranking
    Ranking();
private:
    p rank[10]; //vetor de 10 posições p
    list<players> myRanking; //lista dos 10 primeiros lugares no ranking
    sf::Texture background; //textura do fundo
    sf::Sprite spriteBackground; //sprite do fundo
    sf::Font font; //fonte usada
    sf::Text text; //texto 
};

std::string number(int n); //recebe um inteiro; retorna uma string

#endif
