#include "../ranking.h"
#include "../classmain.h"
#include "../scene_manager.h"

std::string number(int n) //função que transforma um inteiro em uma string
{
    std::stringstream ss;
    ss << n;
    return ss.str();
}

void Ranking::refresh() //função que atualiza o ranking
{
    myRanking.clear(); //limpa a lista do ranking
    read_from_file(); //faz leitura do arquivo ranking.txt
    while(myRanking.size() > 10)
    {
        myRanking.pop_back(); //tira os nós que passam da posição 10
    }

    spriteBackground.setTexture(background);

    int j = 220;
    int ii = 0;

    for(list<players>::iterator i = myRanking.begin(); i != myRanking.end(); i++) //percorre a lista de players
    {
        rank[ii].name.setFont(font); //define fonte
        rank[ii].points.setFont(font); //define fonte
        rank[ii].name.setPosition(130, j); //define posição de name
        rank[ii].points.setPosition(260, j); //define posição de pontos
        rank[ii].name.setString((*i).name); //define o conteúdo 
        rank[ii].points.setString(number((*i).points)); //define o conteúdo
        ii++; j+=30;
    }

}
Ranking::Ranking() //construtor
{
    if (!font.loadFromFile("resources/fonts/Fixedsys500c.ttf")) //carrega a fonte
    {
       std::cout << "Erro ao inicializar a textura" << std::endl;
    }

    if (!background.loadFromFile("resources/images/ranking1.png")) //carrega o fundo
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    refresh(); //chama o método que atualiza 
}

void Ranking::redraw() //redesenha as atualizações 
{
    b_redraw = true; 
    if (b_redraw)
    {
        window.clear(sf::Color::Black); //limpa a tela com preto
        window.draw(spriteBackground); //desenha fundo
        for( int i = 0; i < myRanking.size(); i++) //escreve o nome dos jogadores e a pontuação
        {
            window.draw(rank[i].name); 
            window.draw(rank[i].points);
        }
        window.display();
        b_redraw = false;
    }
}

void Ranking::update() //recebe eventos e faz as mudanças necessárias 
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) //fecha a janela 
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
                //botão para sair
                if(event.mouseButton.x > 12 && event.mouseButton.x < 68 && event.mouseButton.y > 508 && event.mouseButton.y < 532)
                {
                    SceneManager::change_scene(Main::menu); //muda a cena para menu principal
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
                while( i != myRanking.size() && p < myRanking.at(i).points ) i++;
            }
            myRanking.insert(new_player, i);
        }
    }
    entrada.close();
}
