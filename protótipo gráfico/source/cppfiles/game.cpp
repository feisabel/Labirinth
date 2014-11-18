#include "../game.h"
#include "../classmain.h"

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

        int j;
		for (j=0; j<b; j++)
		{
			for (int i=0; i<a; i++)
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
        if( j != b ) {
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

Game::Game()
{
    if (!read_from_file()) return;

    if (!wall.loadFromFile("wall1.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }

    if (!floor.loadFromFile("floor1.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }

    if (!character_back.loadFromFile("char_back.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }

    if (!character_front.loadFromFile("char_front.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }

    if (!character_left.loadFromFile("char_left.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }

    if (!character_right.loadFromFile("char_right.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }



    spriteWall.setTexture(wall);
    spriteFloor.setTexture(floor);
    spriteCharacter.setTexture(character_back);

    player.pos() = maze.entrance();
}


void Game::update()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) //fecha o jogo caso aperte esc
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                Main::quit = true;
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                spriteCharacter.setTexture(character_left);
                player.x()--;
                if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.x()++;
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                spriteCharacter.setTexture(character_right);
                player.x()++;
                if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.x()--;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                spriteCharacter.setTexture(character_front);
                player.y()++;
                if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.y()--;
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                spriteCharacter.setTexture(character_back);
                player.y()--;
                if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.y()++;
            }
        }
    }
}


void Game::redraw()
{
    window.clear(sf::Color::Black);

    int y = (WINDOW_HEIGHT - 5*56)/2;
    for( int j = player.y()-2; j <= player.y()+2; j++, y+=56 )
    {
    	int x = (WINDOW_WIDTH - 5*56)/2;
        for( int i = player.x()-2; i <= player.x()+2; i++, x+=56 )
        {
            if( maze.in_bounds(Position(i, j)) )
            {
                if (maze[i][j].type() == Block::FLOOR)
                {
                    spriteFloor.setPosition(sf::Vector2f(x, y));
                    window.draw(spriteFloor);
                }
                else
                {
                    spriteWall.setPosition(sf::Vector2f(x, y));
                    window.draw(spriteWall);
                }

                if(player.x() == i && player.y() == j)
                {
                    spriteCharacter.setPosition(sf::Vector2f(x, y));
                    window.draw(spriteCharacter);
                }
            }
        }
    }

    window.display();
}
