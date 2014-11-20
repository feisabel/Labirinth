#include "../menu.h"
#include "../classmain.h"
#include "../scene_manager.h"

Menu::Menu()
{
    if (!background.loadFromFile("resources/images/prototype1.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    spriteBackground.setTexture(background);
}


void Menu::redraw()
{
    window.clear(sf::Color::Black);
    window.draw(spriteBackground);
    window.display();

}


void Menu::update()
{
    // check all the window's events that were triggered since the last iteration of the loop
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
                if(event.mouseButton.x > 332 && event.mouseButton.x < 473 && event.mouseButton.y > 241 && event.mouseButton.y < 284)
                {
                    SceneManager::change_scene(Main::game);
                }
                if(event.mouseButton.x > 332 && event.mouseButton.x < 473 && event.mouseButton.y > 310 && event.mouseButton.y < 350)
                {
                    //howtoplay
                }
                if(event.mouseButton.x > 332 && event.mouseButton.x < 473 && event.mouseButton.y > 379 && event.mouseButton.y < 415)
                {
                    //ranking;
                }
                if(event.mouseButton.x > 332 && event.mouseButton.x < 473 && event.mouseButton.y > 445 && event.mouseButton.y < 483)
                {
                    Main::quit = true;
                }
            }
        }
    }

}
