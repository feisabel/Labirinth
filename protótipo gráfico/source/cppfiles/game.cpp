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

    sf::Texture character_back;
    if (!character_back.loadFromFile("char_back.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    sf::Texture character_front;
    if (!character_front.loadFromFile("char_front.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    sf::Texture character_left;
    if (!character_left.loadFromFile("char_left.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    sf::Texture character_right;
    if (!character_right.loadFromFile("char_right.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }


    sf::Sprite spriteWall;
    spriteWall.setTexture(wall);
    sf::Sprite spriteFloor;
    spriteFloor.setTexture(floor);
    sf::Sprite spriteCharacter;
    spriteCharacter.setTexture(character_back);

    int i, j;

    player.pos() = maze.entrance();

    while(window->isOpen())
    {
        window->clear(sf::Color::Black);
        sf::Event event;
        while(window->pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed) //fecha o jogo caso aperte esc
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    return;
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    spriteCharacter.setTexture(character_left);
                    player.y()--;
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.y()++;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    spriteCharacter.setTexture(character_right);
                    player.y()++;
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.y()--;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    spriteCharacter.setTexture(character_front);
                    player.x()++;
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.x()--;
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    spriteCharacter.setTexture(character_back);
                    player.x()--;
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.x()++;
                }
            }
        }


        //Position playPosition = maze.entrance();

        /* //calcular índices
        if(playPosition.x-1 < 0)
            playPosition.x = 1;

        if(playPosition.y-1 < 0)
            playPosition.y = 1;

        if(playPosition.x+1 >= maze.cols())
            playPosition.x-=1;

        if(playPosition.y+1 >= maze.rows())
            playPosition.y-=1;
        */

        int x, y = 200, z;
        for( z = 0, i = player.x()-1; i <= player.x()+1; i++, y+=56 )
        {
            for( x = 300, j = player.y()-1; j <= player.y()+1; j++, x+=56, z++ )
            {
                if( maze.in_bounds(Position(i, j)) )
                {
                    if (maze[i][j].type() == Block::FLOOR)
                    {
                        spriteFloor.setPosition(sf::Vector2f(x, y));
                        window->draw(spriteFloor);
                    }
                    else
                    {
                        spriteWall.setPosition(sf::Vector2f(x, y));
                        window->draw(spriteWall);
                    }

                    if(z == 4)
                    {
                        spriteCharacter.setPosition(sf::Vector2f(x, y));
                        window->draw(spriteCharacter);
                    }
                }
            }
        }
        window->display();
    }
}
