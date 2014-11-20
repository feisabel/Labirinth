#include "../classmain.h"
#include "../menu.h"
#include "../game.h"
#include "../menucontinue.h"
#include "../scene_manager.h"

MenuContinue::MenuContinue()
{
        if (!font.loadFromFile("journal.ttf"))
    {
       std::cout << "Erro ao inicializar a textura" << std::endl;
    }

    for(int c = 0; c < 3; c++)
    {
        button[c].content.setFont(font);
        button[c].content.setCharacterSize(32);
    }

    title_teste.setSize(sf::Vector2f(150, 75));
    title_teste.setPosition(sf::Vector2f(100, 100));
    title_teste.setFillColor(sf::Color(0, 128, 255));

    title.setCharacterSize(40);
    title.setFont(font);
    title.setColor(sf::Color::White);
    title.setString("Under Paris");
    title.setPosition(sf::Vector2f(110,100));

    for( int c = 0, rectY = 300; c < 3; c++, rectY+= 80)
    {
        button[c].rect.setSize(sf::Vector2f(150, 50));
        button[c].setPosition(sf::Vector2f(300, rectY));
        button[c].rect.setFillColor(sf::Color(0, 128, 255));

        button[c].content.setColor(sf::Color::White);

        if (c == 0) {
            button[c].content.setString("Resume");
        }
        if (c == 1) {
            button[c].content.setString("Restart");
        }
        if (c == 2) {
            button[c].content.setString("Menu");
        }
    }
}

void MenuContinue::redraw()
{
    window.clear(sf::Color::Black);
    window.draw(title_teste);
    window.draw(title);

    //BOTÕES DO MENU
    for( int c = 0; c < 3; c++)
    {
        window.draw(button[c].rect); //DESENHA
        window.draw(button[c].content);
    }

    window.display();
}

void MenuContinue::update()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            Main::quit = true;
        if (event.type == sf::Event::KeyPressed) //fecha o jogo caso aperte esc
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                Main::quit = true;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if(event.mouseButton.x > 300 && event.mouseButton.x < 500 && event.mouseButton.y > 300 && event.mouseButton.y < 345)
                {
                    SceneManager::change_scene(Main::game);
                }
                if(event.mouseButton.x > 300 && event.mouseButton.x < 500 && event.mouseButton.y > 380 && event.mouseButton.y < 425)
                {
                    Main::game.restart();
                    SceneManager::change_scene(Main::game);
                }
                if(event.mouseButton.x > 300 && event.mouseButton.x < 500 && event.mouseButton.y > 460 && event.mouseButton.y < 505)
                {
                    SceneManager::change_scene(Main::menu);
                }
            }
        }
    }
}
