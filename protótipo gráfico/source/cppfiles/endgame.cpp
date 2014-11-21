#include "../endgame.h"
#include "../classmain.h"
#include "../scene.h"
#include "../scene_manager.h"
#include "../game.h"
#include <SFML/System/String.hpp>
#include <string>
#include <sstream>

EndGame::EndGame()
{
    std::stringstream ss;
    ss << Main::game.player.points();
    points = ss.str();

    if (!font.loadFromFile("resources/fonts/Fixedsys500c.ttf"))
    {
       std::cout << "Erro ao inicializar a textura" << std::endl;
    }
    text1.setCharacterSize(40);
    text1.setFont(font);
    text1.setColor(sf::Color::White);
    text1.setString("Parabains");
    text1.setPosition(sf::Vector2f(175,200));

    text2.setCharacterSize(30);
    text2.setFont(font);
    text2.setColor(sf::Color::White);
    text2.setString("Your name:");
    text2.setPosition(sf::Vector2f(170,260));

    text3.setCharacterSize(30);
    text3.setFont(font);
    text3.setColor(sf::Color::White);
text3.setPosition(sf::Vector2f(170,295));

    text4.setCharacterSize(20);
    text4.setFont(font);
    text4.setColor(sf::Color::White);
    text4.setString("Press esc to exit");
    text4.setPosition(sf::Vector2f(150,500));

    text5.setCharacterSize(30);
    text5.setFont(font);
    text5.setColor(sf::Color::White);
    text5.setString("Points: "+ points);
    text5.setPosition(sf::Vector2f(170,330));
}

void EndGame::update(){


    std::string a;

    sf::Event event;
    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            Main::quit = true;
        if (event.type == sf::Event::KeyPressed) //fecha o jogo caso aperte esc
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                Main::game.restart();
                SceneManager::change_scene(Main::menu);
            }
            if (event.key.code == sf::Keyboard::BackSpace)
            {
                str = str.substr( 0, (str.size() -1));
                text3.setString(str);
            }
        }
        if (event.type == sf::Event::TextEntered)
        {
            // Handle ASCII characters only
            if (event.text.unicode < 128 && event.text.unicode != 8)
            {
                a = static_cast<char>(event.text.unicode);
                str+=a;
                text3.setString(str);
                std::cout << str << std::endl;
            }
        }
    }
}

void EndGame::redraw(){
    b_redraw = true;
    if (b_redraw)
    {
        window.clear(sf::Color(51, 34, 60));
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(text5);
        window.display();
        b_redraw = false;
    }
}
