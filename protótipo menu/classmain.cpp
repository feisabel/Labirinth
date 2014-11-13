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
                        startGame();
                        //Cogitar colocar nível
                        //Declara jogo e inicia
                    }
                    if(event.mouseButton.x > 300 && event.mouseButton.x < 500 && event.mouseButton.y > 380 && event.mouseButton.y < 425)
                    {
                        //credits();
                    }
                    if(event.mouseButton.x > 300 && event.mouseButton.x < 500 && event.mouseButton.y > 460 && event.mouseButton.y < 505)
                    {
                        howToPlay();
                    }
                }
            }
        } //FIM DA LEITURA DE EVENTOS

        // INÍCIO DA TELA
        window.clear(sf::Color::Black); // Limpa a tela e coloca para preta

        // Variáveis de botões
        sf::RectangleShape buttonInit(sf::Vector2f(200, 45));
        sf::RectangleShape title_teste(sf::Vector2f(300, 45)); //título
        // Variáveis de texto
        sf::Font font;
        if (!font.loadFromFile("journal.ttf"))
        {
           std::cout <<"Erro ao inicializar a textura" << std::endl;
           window.close();
        }

        sf::Text text;
        sf::Text title;

        text.setFont(font);
        title.setPosition(sf::Vector2f(110,100));
        text.setCharacterSize(32);


        title_teste.setPosition(sf::Vector2f(100, 100));
        title_teste.setFillColor(sf::Color(0, 128, 255));
        title.setCharacterSize(40);
        title.setFont(font);
        title.setColor(sf::Color::Black);
        title.setString("O Labirinto");
        window.draw(title_teste);
        window.draw(title);
        //BOTÕES DO MENU
        for( int c = 0, rectY = 300; c < 3; c++, rectY+= 80)
        {
            buttonInit.setPosition(sf::Vector2f(300, rectY));
            buttonInit.setFillColor(sf::Color(0, 128, 255));

            //BOTAO INICIAR
            if (c == 0) {
                text.setPosition(sf::Vector2f(380,rectY+5));
                text.setString("Play");
            }
            //BOTAO CRÉDITOS
            if (c == 1) {
                text.setPosition(sf::Vector2f(370,rectY+5));
                text.setString("Credits");
            }
            //BOTAO RANKING
            if (c == 2) {
                text.setPosition(sf::Vector2f(370,rectY+5));
                text.setString("How to play");
            }
            window.draw(buttonInit); //DESENHA
            window.draw(text);
        }
        window.display(); //ATUALIZA A TELA

        //ONDE A MAGIA ACONTECE
    }
}

void Main::howToPlay()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Labirinto");
    window.clear(sf::Color::Black); // Limpa a tela e coloca para preta
    while(window.isOpen())
    {
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
        }

        sf::RectangleShape box(sf::Vector2f(700, 500));
        sf::Font font;
        if (!font.loadFromFile("journal.ttf"))
        {
            std::cout <<"Erro ao inicializar a textura" << std::endl;
            window.close();
        }
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(32);
        box.setPosition(sf::Vector2f(50, 50));
        box.setFillColor(sf::Color(153, 153, 255));
        text.setColor(sf::Color::Black);
        text.setPosition(sf::Vector2f(100,100));
        text.setString("How to play");
        window.draw(box);
        window.draw(text);
        window.display();
    }
}

void Main::startGame()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Labirinto");
    window.clear(sf::Color::Black); // Limpa a tela e coloca para preta
    while(window.isOpen())
    {
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
        }

        sf::RectangleShape box(sf::Vector2f(700, 500));
        sf::Font font;
        if (!font.loadFromFile("journal.ttf"))
        {
            std::cout <<"Erro ao inicializar a textura" << std::endl;
            window.close();
        }
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(32);
        box.setPosition(sf::Vector2f(50, 50));
        box.setFillColor(sf::Color(153, 153, 255));
        text.setColor(sf::Color::Black);
        text.setPosition(sf::Vector2f(100,100));
        text.setString("Game");
        window.draw(box);
        window.draw(text);
        window.display();
    }

}
