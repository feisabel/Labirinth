#include "../menu.h"
#include "../classmain.h"
#include "../scene_manager.h"

howToPlay::howToPlay() //Construtor padrão
{
    if (!background.loadFromFile("resources/images/how_to_play1.png")) // carrega imagem da textura
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    spriteBackground.setTexture(background);
}


void howToPlay::redraw()
{
    b_redraw = true; // alterei aqui
    if (b_redraw)
    {
        window.clear(sf::Color::Black);
        window.draw(spriteBackground);
        window.display();

        b_redraw = false;
    }
}

void howToPlay::update()
{   
    // Checa todos os eventos da janela que foram ativados desde a última iteração do loop.
    sf::Event event;
    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) // fechar janela
            Main::quit = true;
        if (event.type == sf::Event::KeyPressed) // Fecha o jogo caso aperte ESC.
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                Main::quit = true;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left) // caso tenha apertado o botão bach
            {
                if(event.mouseButton.x > 12 && event.mouseButton.x < 68 && event.mouseButton.y > 508 && event.mouseButton.y < 532)
                {
                    SceneManager::change_scene(Main::menu);
                }
            }
        }
    }
}

