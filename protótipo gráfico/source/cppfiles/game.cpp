#include "../game.h"
#include <fstream>
#include <iostream>

// Função que forma o labririnto conforme as informações do arquivo de entrada e modifica entrance e exit
bool Game::read_from_file()
{
	std::ifstream entrada; 							   // Conexão com o arquivo "entrada.txt".

	entrada.open ( "entrada.txt", std::ifstream::in ); // Abre o arquivo "entrada.txt".

	if( entrada.is_open() ) {
		int a, b;

		if( !(entrada >> a) )
		{
			entrada.close();
			std::cout << "não leu a" << std::endl;
			return false;
		}
		if( !(entrada >> b) )
		{
			entrada.close();
			std::cout << "não leu a" << std::endl;
			return false;
		}

		maze.init(a, b);

		int i;
		for (i=0; i<a; i++)
		{
			for (int j=0; j<b; j++)
			{
				int x;
				entrada >> x;

				if (x == 1) maze[i][j].type() = Block::WALL;
				else
				{
					maze[i][j].type() = Block::FLOOR;

					if (x == 2) maze.entrance() = Position(i, j);
					else if (x == 3) maze.exit() = Position(i, j);
					else if (x == 4)
					{
						Trap t;
						t.pos() = Position(i, j);
						traps.push_back(t);
					}
					else if (x == 5)
					{
						Spawn s;
						s.pos() = Position(i, j);
						spawns.push_back(s);
					}
					else if (x == 6)
					{
						Item h;
						h.pos() = Position(i, j);
						hearts.push_back(h);
					}
					else if (x == 7)
					{
						Item a;
						a.pos() = Position(i, j);
						ammuns.push_back(a);
					}
					else if (x == 8)
					{
						Enemy e;
						e.pos() = Position(i, j);
						enemies.push_back(e);
					}
				}
			}
		}
        // Verifica se a leitura da matriz ocorreu corretamente.
        if( i != a ) {
        	std::cout << "não leu matriz" << std::endl;
        	entrada.close();
        	return false;
        }
	}
	else {
		std::cout << "não abriu arquivo" << std::endl;
		entrada.close();
		return false;
	}

	entrada.close();
	return true;
}

void Game::init(sf::RenderWindow* window)
{
    sf::Texture wall;
    if (!wall.loadFromFile("wall1.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    sf::Texture floor;
    if (!floor.loadFromFile("floor1.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    sf::Sprite spriteWall;
    spriteWall.setTexture(wall);
    sf::Sprite spriteFloor;
    spriteWall.setTexture(floor);

    int i, j;
    window->clear(sf::Color::Black);
    while(window->isOpen())
    {
         sf::Event event;
         while(window->pollEvent(event)){
             if (event.type == sf::Event::KeyPressed) //fecha o jogo caso aperte esc
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        return;
                    }
                }
         }
        //vai ler a matriz e imprimir
        //nove blocos, jogador no meio
        Position playPosition = maze.entrance();
        //pega as coordenadas do jogador e imprime ao redor dele
        //calcular índices
        //fazer função que pega x e y
        if(playPosition.x-1 < 0)
            playPosition.x = 1;

        if(playPosition.y-1 < 0)
            playPosition.y = 1;
        int x, y = 300;
        bool test;
        std::cout << playPosition.x << " " << playPosition.y;
        for(i = playPosition.x-1; i <= playPosition.x+1; i++, y+=56)
        {
            for(x = 300, j = playPosition.y-1; j <= playPosition.y+1; j++, x+=56 )
            {
                if(maze[i][j].type() == Block::WALL)
                {
                    spriteWall.setPosition(sf::Vector2f(x, y));
                    //std::cout << "aqui" << std::endl;

                    test = true;
                    //imprime parede
                }
                else
                {
                    test = false;
                    spriteFloor.setPosition(sf::Vector2f(x, y));
                    //std::cout << "aqui2" << std::endl;


                    //imprime caminho
                }
                if( test )
                {
                    window->draw(spriteWall);
                }
                else
                {
                    window->draw(spriteFloor);
                }

            }
        }
        window->display();
    }
    return;
}
