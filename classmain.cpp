#include "classmain.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

void Main::menu(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Labirinto");

    //window.setFramerateLimit(30);
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed) //fecha o jogo caso aperte esc
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if(event.mouseButton.x > 300 && event.mouseButton.x < 500 && event.mouseButton.y > 300 && event.mouseButton.y < 345)
                    {
                        //Cogitar colocar nível
                        //Declara jogo e inicia
                    }
                    if(event.mouseButton.x > 300 && event.mouseButton.x < 500 && event.mouseButton.y > 380 && event.mouseButton.y < 425)
                    {
                        //Créditos
                    }
                    if(event.mouseButton.x > 300 && event.mouseButton.x < 500 && event.mouseButton.y > 460 && event.mouseButton.y < 505)
                    {
                        //Créditos
                    }
                }
            }
        } //FIM DA LEITURA DE EVENTOS

        // INÍCIO DA TELA
        window.clear(sf::Color::Red); // Limpa a tela e coloca para preta

        // Variáveis de botões
        sf::RectangleShape buttonInit(sf::Vector2f(200, 45));
        sf::RectangleShape title_teste(sf::Vector2f(300, 45)); //título
        // Variáveis de texto
        sf::Font font;
        if (!font.loadFromFile("Walkway_Black.ttf"))
        {
           std::cout <<"Erro ao inicializar a textura" << std::endl;
           window.close();
        }

        sf::Text text;
        sf::Text title;

        text.setFont(font);
        title.setPosition(sf::Vector2f(110,110));
        text.setCharacterSize(24);


        title_teste.setPosition(sf::Vector2f(100, 100));
        title_teste.setFillColor(sf::Color(0, 128, 255));
        title.setCharacterSize(32);
        title.setFont(font);
        title.setColor(sf::Color::White);
        title.setString("O Labirinto");
        window.draw(title);
        window.draw(title_teste);

        //BOTÕES DO MENU
        for( int c = 0, rectY = 300; c < 3; c++, rectY+= 80)
        {
            buttonInit.setPosition(sf::Vector2f(300, rectY));
            buttonInit.setFillColor(sf::Color(0, 128, 255));

            //BOTAO INICIAR
            if (c == 0) {
                text.setPosition(sf::Vector2f(370,rectY+5));
                text.setString("Jogar");
            }
            //BOTAO CRÉDITOS
            if (c == 1) {
                text.setString("Creditos");
            }
            //BOTAO RANKING
            if (c == 2) {
                text.setString("Ranking");
            }
            window.draw(buttonInit); //DESENHA
            window.draw(text);
        }
        window.display(); //ATUALIZA A TELA

        //ONDE A MAGIA ACONTECE
    }
}

