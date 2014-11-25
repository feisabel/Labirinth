#include "../classmain.h"
#include "../menu.h"
#include "../game.h"
#include "../menucontinue.h"
#include "../scene_manager.h"

MenuContinue::MenuContinue() //construtor padrão
{
    if (!font.loadFromFile("resources/fonts/Fixedsys500c.ttf")) //carrega as texturas com suas imagens
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
    //carrega os sprites com suas texturas
    spriteExit.setTexture(exit); 
    spriteExit.setPosition(sf::Vector2f(300,430)); //modifica a posição do sprite
    spriteMenu.setTexture(menu);
    spriteMenu.setPosition(sf::Vector2f(300,370)); 
    spriteRestart.setTexture(restart);
    spriteRestart.setPosition(sf::Vector2f(300,310));
    spriteResume.setTexture(resume);
    spriteResume.setPosition(sf::Vector2f(300,250));
    title.setCharacterSize(40); //define tamanho da letra
    title.setFont(font); //define fonte
    title.setColor(sf::Color::White); //define cor
    title.setString("Under Paris"); //define conteúdo do texto
    title.setPosition(sf::Vector2f(110,100)); //define posição

    rect.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)); //define o tamanho do rect como o tamanho da janela
    rect.setFillColor(sf::Color(0, 0, 0, 170)); //define 
}

//método que redesenha as atualizações na tabela
void MenuContinue::redraw()
{
    if (b_redraw)
    {
        window.draw(rect);
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

//métudo que faz atualizações 
void MenuContinue::update()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) //fecha janela
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
                //botão para voltar ao jogo
                if(event.mouseButton.x > 300 && event.mouseButton.x < 450 && event.mouseButton.y > 250 && event.mouseButton.y < 295)
                {
                    SceneManager::change_scene(Main::game);
                }
                //botão para reiniciar o jogo
                if(event.mouseButton.x > 300 && event.mouseButton.x < 450 && event.mouseButton.y > 310 && event.mouseButton.y < 455)
                {
                    Main::game.restart();
                    SceneManager::change_scene(Main::game);
                }
                //botão para menu
                if(event.mouseButton.x > 300 && event.mouseButton.x < 450 && event.mouseButton.y > 370 && event.mouseButton.y < 415)
                {
                    Main::game.playMusic(false);
                    SceneManager::change_scene(Main::menu);
                }
                //botão para sair
                if(event.mouseButton.x > 300 && event.mouseButton.x < 450 && event.mouseButton.y > 430 && event.mouseButton.y < 475)
                {
                    Main::quit = true;
                }
            }
        }
    }
}
