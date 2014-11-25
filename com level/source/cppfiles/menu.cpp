#include "../menu.h"
#include "../classmain.h"
#include "../scene_manager.h"

Menu::Menu() // construtor padrão 
{
    if (!background.loadFromFile("resources/images/prototype1.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    spriteBackground.setTexture(background);
}


void Menu::redraw() // redesenha as atualizações na tela
{
    b_redraw = true;
    if (b_redraw)
    {
        window.clear(sf::Color::Black);
        window.draw(spriteBackground);
        window.display();

        b_redraw = false;
    }
}

void Menu::update()
{
    sf::Event event; // cria evento 
    while(window.pollEvent(event)) // pega os eventos para tratar
    {
        if (event.type == sf::Event::Closed) // chega a janela
            Main::quit = true;
        if (event.type == sf::Event::KeyPressed) 
        {
            if (event.key.code == sf::Keyboard::Escape) // fecha o jogo caso aperte esc
            {
                Main::quit = true;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // botão para play
                if(event.mouseButton.x > 332 && event.mouseButton.x < 473 && event.mouseButton.y > 241 && event.mouseButton.y < 284)
                {
                    Main::game.player.p_start();
                    Main::game.playMusic(true);
                    SceneManager::change_scene(Main::game);
                }
                // botão para how to play
                if(event.mouseButton.x > 332 && event.mouseButton.x < 473 && event.mouseButton.y > 310 && event.mouseButton.y < 350)
                {
                    SceneManager::change_scene(Main::howtoplay);
                }
                // botão para ranking
                if(event.mouseButton.x > 332 && event.mouseButton.x < 473 && event.mouseButton.y > 379 && event.mouseButton.y < 415)
                {
                    SceneManager::change_scene(Main::ranking);
                }
                // botão para sair
                if(event.mouseButton.x > 332 && event.mouseButton.x < 473 && event.mouseButton.y > 445 && event.mouseButton.y < 483)
                {
                    Main::quit = true;
                }
            }
        }
    }

}
