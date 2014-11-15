#include "scene.h"
#include "classmain.h"

sf::RenderWindow SceneManager::window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "Labirinto");

void Menu::draw()
{
        window.clear(sf::Color::Black);
        if (!font.loadFromFile("journal.ttf"))
        {
           std::cout <<"Erro ao inicializar a textura" << std::endl;
           window.close();
        }


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
                text.setPosition(sf::Vector2f(360,rectY+5));
                text.setString("How to play");
            }
            window.draw(buttonInit); //DESENHA
            window.draw(text);
        }

}
void Menu::display()
{
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
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
                        //startGame(&window);
                        //Cogitar colocar nível
                        //Declara jogo e inicia
                    }
                    if(event.mouseButton.x > 300 && event.mouseButton.x < 500 && event.mouseButton.y > 380 && event.mouseButton.y < 425)
                    {
                        //credits();
                    }
                    if(event.mouseButton.x > 300 && event.mouseButton.x < 500 && event.mouseButton.y > 460 && event.mouseButton.y < 505)
                    {
                        //howToPlay(&window);
                    }
                }
            }
        }
        window.display();
    }
}
