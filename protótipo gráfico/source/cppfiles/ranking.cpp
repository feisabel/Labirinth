#include "../ranking.h"
#include "../classmain.h"
#include "../scene_manager.h"

std::string number(int n)
{
    std::stringstream ss;
    ss << n;
    return ss.str();
}

void Ranking::refresh()
{
    myRanking.clear();
    read_from_file();
    while(myRanking.size() > 10)
    {
        myRanking.pop_back();
    }

    spriteBackground.setTexture(background);

    int j = 220;
    int ii = 0;

    for(list<players>::iterator i = myRanking.begin(); i != myRanking.end(); i++)
    {
        rank[ii].name.setFont(font);
        rank[ii].points.setFont(font);
        rank[ii].name.setPosition(130, j);
        rank[ii].points.setPosition(260, j);
        rank[ii].name.setString((*i).name);
        rank[ii].points.setString(number((*i).points));
        ii++; j+=30;
    }

}
Ranking::Ranking()
{
    if (!font.loadFromFile("resources/fonts/Fixedsys500c.ttf"))
    {
       std::cout << "Erro ao inicializar a textura" << std::endl;
    }

    if (!background.loadFromFile("resources/images/ranking1.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    refresh();
}

void Ranking::redraw()
{
    b_redraw = true; //alterei aqui
    if (b_redraw)
    {
        window.clear(sf::Color::Black);
        window.draw(spriteBackground);
        for( int i = 0; i < myRanking.size(); i++)
        {
            window.draw(rank[i].name); //PROBLEMA AQUI
            window.draw(rank[i].points);
        }
        window.display();
        b_redraw = false;
    }
}

void Ranking::update()
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
                if(event.mouseButton.x > 12 && event.mouseButton.x < 68 && event.mouseButton.y > 508 && event.mouseButton.y < 532)
                {
                    SceneManager::change_scene(Main::menu);
                }
            }
        }
    }
}

void Ranking::read_from_file()
{
    std::ifstream entrada;
    char name[10];
    players new_player;
    int p;
    entrada.open( "levels/ranking.txt", std::ifstream::in );
    if( entrada.is_open() )
    {
        while((entrada >> name) && (entrada >> p))
        {
            std::string name_i(name);
            new_player.add_information(name_i, p);
            int i = 0;
            if(!myRanking.empty())
            {
                while( p < myRanking.at(i).points && i+1 != myRanking.size() )
            i++;
            }
            myRanking.insert(new_player, i);
        }
    }
    entrada.close();
}
