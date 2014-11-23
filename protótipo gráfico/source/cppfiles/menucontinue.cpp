#include "../classmain.h"
#include "../menu.h"
#include "../game.h"
#include "../menucontinue.h"
#include "../scene_manager.h"

MenuContinue::MenuContinue()
{
    if (!font.loadFromFile("resources/fonts/Fixedsys500c.ttf"))
    {
       std::cout << "Erro ao inicializar a textura" << std::endl;
    }

    if (!exit.loadFromFile("resources/images/button_exit_off.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }

    if (!resume.loadFromFile("resources/images/button_resume_off.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }

    if (!menu.loadFromFile("resources/images/button_menu_off.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    if (!restart.loadFromFile("resources/images/button_restart_off.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }

    spriteExit.setTexture(exit);
    spriteExit.setPosition(sf::Vector2f(300,430));
    spriteMenu.setTexture(menu);
    spriteMenu.setPosition(sf::Vector2f(300,370));
    spriteRestart.setTexture(restart);
    spriteRestart.setPosition(sf::Vector2f(300,310));
    spriteResume.setTexture(resume);
    spriteResume.setPosition(sf::Vector2f(300,250));
    title.setCharacterSize(40);
    title.setFont(font);
    title.setColor(sf::Color::White);
    title.setString("Under Paris");
    title.setPosition(sf::Vector2f(110,100));

    rect.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    rect.setFillColor(sf::Color(0, 0, 0, 170));


}

void MenuContinue::redraw()
{
    if (b_redraw)
    {
        window.draw(title);
        window.draw(spriteExit);
        window.draw(spriteMenu);
        window.draw(spriteRestart);
        window.draw(spriteResume);
        //BOTÕES DO MENU

        window.display();
        b_redraw = false;
    }
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
                SceneManager::change_scene(Main::game);
            }
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if(event.mouseButton.x > 300 && event.mouseButton.x < 450 && event.mouseButton.y > 250 && event.mouseButton.y < 295)
                {
                    Main::game.restart();
                    SceneManager::change_scene(Main::game);
                }
                if(event.mouseButton.x > 300 && event.mouseButton.x < 450 && event.mouseButton.y > 310 && event.mouseButton.y < 455)
                {
                    SceneManager::change_scene(Main::game);
                }
                if(event.mouseButton.x > 300 && event.mouseButton.x < 450 && event.mouseButton.y > 370 && event.mouseButton.y < 415)
                {
                    Main::game.playMusic(false);
                    SceneManager::change_scene(Main::menu);
                }
                if(event.mouseButton.x > 300 && event.mouseButton.x < 450 && event.mouseButton.y > 430 && event.mouseButton.y < 475)
                {
                    Main::quit = true;
                }
            }
        }
    }
}
