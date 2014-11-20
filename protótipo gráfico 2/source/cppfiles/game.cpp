#include "../menu.h"
#include "../game.h"
#include "../classmain.h"
#include "../menucontinue.h"
#include "../scene.h"
#include "../scene_manager.h"
#include "../enemy.h"
#include "../item.h"
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
						Item h(true);
						h.pos() = Position(i, j);
						hearts.push_back(h);
					}
					else if (x == 7)
					{
						Item a(false);
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

    if (!trap_off.loadFromFile("trap_off3.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }

    if (!trap_on.loadFromFile("trap_on3.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }

    if (!spawn.loadFromFile("spawn1.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }

    if (!monster_front.loadFromFile("skeleton_front.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }

    if (!ammo.loadFromFile("ammo.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }

    if (!med.loadFromFile("medkit.png"))
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
    
    if (!bullet_down.loadFromFile("bullet_down.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    
    if (!bullet_up.loadFromFile("bullet_up.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    
    if (!bullet_left.loadFromFile("bullet_left.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    
    if (!bullet_right.loadFromFile("bullet_right.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }



    spriteWall.setTexture(wall);
    spriteFloor.setTexture(floor);
    spriteTrap.setTexture(trap_off);
    spriteSpawn.setTexture(spawn);
    spriteMonster.setTexture(monster_front);
    spriteAmmo.setTexture(ammo);
    spriteMed.setTexture(med);
    spriteCharacter.setTexture(character_back);
    spriteBullet.setTexture(bullet_down);

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
                SceneManager::change_scene(Main::menucontinue);
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                spriteCharacter.setTexture(character_left);
                if( player.direction() == 'l')
                {
                    player.x()--;
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.x()++;
                }
                player.direction('l');
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                spriteCharacter.setTexture(character_right);
                if( player.direction() == 'r')
                {
                    player.x()++;
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.x()--;
                }
                player.direction('r');
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                spriteCharacter.setTexture(character_front);
                if( player.direction() == 'd')
                {
                    player.y()++;
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.y()--;
                }
                player.direction('d');
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                spriteCharacter.setTexture(character_back);
                if( player.direction() == 'u')
                {
                    player.y()--;
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.y()++;
                }
                player.direction('u');
            }
            else if (event.key.code == sf::Keyboard::Z)
            {
                useAmount();
            }
            else if (event.key.code == sf::Keyboard::Space && bullet_course.empty())
            {
                fire();
            }
        }
    }
    //active_traps();
}

void Game::useAmount()
{
    int i;
    Item t(true);
    list<Item>::iterator it;
    for(it = hearts.begin(), i = 0; it != hearts.end(); it++, i++)
    {
        t = *it;
        if(t.pos() == player.pos()){
            t = hearts.erase(i);
            player.change_hp(t.amount());
        }
    }
    for(it = ammuns.begin(), i = 0; it != ammuns.end(); it++, i++)
    {
        t = *it;
        if(t.pos() == player.pos()){
            t = ammuns.erase(i);
            player.change_ammo(t.amount());
        }
    }
}
/*void Game::active_traps()
{
    for(int i = 0; i < traps.size(); i++)
    {
        Trap *t = &traps.at(i);
        if(t->is_active())
            t->activate();
        else
            t->disactivate();
    }
}*/

bool Game::showMonster(int i, int j)
{
    Position a(i, j);
    Enemy e;
    for(list<Enemy>::iterator i = enemies.begin(); i != enemies.end(); i++)
    {
        e = *i;
        if(e.pos() == a)
        {
            return true;
        }
    }
    return false;
}

bool Game::showMed(int i, int j)
{
    Position a(i, j);
    Item e(true);
    for(list<Item>::iterator i = hearts.begin(); i != hearts.end(); i++)
    {
        e = *i;
        if(e.pos() == a)
        {
            return true;
        }
    }
    return false;
}

bool Game::showTrap(int i, int j)
{
    Position a(i, j);
    Trap e;
    for(list<Trap>::iterator i = traps.begin(); i != traps.end(); i++)
    {
        e = *i;
        if(e.pos() == a && e.is_active())
        {
            spriteTrap.setTexture(trap_on);
            return true;
        }
        else if( e.pos() == a && !e.is_active())
        {
            spriteTrap.setTexture(trap_off);
            return true;
        }
    }
    return false;
}

bool Game::showAmmo(int i, int j)
{
    Position a(i, j);
    Item e(false);
    for(list<Item>::iterator i = ammuns.begin(); i != ammuns.end(); i++)
    {
        e = *i;
        if(e.pos() == a)
            return true;
    }
    return false;
}

bool Game::showSpawn(int i, int j)
{
    Position a(i, j);
    Spawn e;
    for(list<Spawn>::iterator i = spawns.begin(); i != spawns.end(); i++)
    {
        e = *i;
        if(e.pos() == a)
            return true;
    }
    return false;
}

void Game::fire()
{
    Entity bullet(player.x(), player.y());
    Position pos;
    if (player.direction() == 'l')
    {
        spriteBullet.setTexture(bullet_left);
        bullet.x()--;
        pos.y = bullet.y();
        while (maze.in_bounds(bullet.pos()) && maze[bullet.x()][bullet.y()].type() != Block::WALL)
        {
            pos.x = bullet.x();
            bullet_course.push( pos );
            bullet.x()--;
        }
    }
    else if (player.direction() == 'r')
    {
        spriteBullet.setTexture(bullet_right);
        bullet.x()++;
        pos.y = bullet.y();
        while (maze.in_bounds(bullet.pos()) && maze[bullet.x()][bullet.y()].type() != Block::WALL)
        {
            pos.x = bullet.x();
            bullet_course.push( pos );
            bullet.x()++;
        }
    }
    else if (player.direction() == 'u')
    {
        spriteBullet.setTexture(bullet_up);
        bullet.y()--;
        pos.x = bullet.x();
        while (maze.in_bounds(bullet.pos()) && maze[bullet.x()][bullet.y()].type() != Block::WALL)
        {
            pos.y = bullet.y();
            bullet_course.push( pos );
            bullet.y()--;
        }
    }
    else
    {
        spriteBullet.setTexture(bullet_down);
        bullet.y()++;
        pos.x = bullet.x();
        while (maze.in_bounds(bullet.pos()) && maze[bullet.x()][bullet.y()].type() != Block::WALL)
        {
            pos.y = bullet.y();
            bullet_course.push( pos );
            bullet.y()++;
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

                if(showSpawn(i, j))
                {
                    spriteSpawn.setPosition(sf::Vector2f(x, y));
                    window.draw(spriteSpawn);
                }

                if(showMonster(i, j))
                {
                    spriteMonster.setPosition(sf::Vector2f(x, y));
                    window.draw(spriteMonster);
                }

                if(showAmmo(i, j))
                {
                    spriteAmmo.setPosition(sf::Vector2f(x, y));
                    window.draw(spriteAmmo);
                }

                if(showMed(i, j))
                {
                    spriteMed.setPosition(sf::Vector2f(x, y));
                    window.draw(spriteMed);
                }

                if(showTrap(i, j))
                {
                    spriteTrap.setPosition(sf::Vector2f(x, y));
                    window.draw(spriteTrap);
                }
                
                if(!bullet_course.empty() && bullet_course.front().x == i && bullet_course.front().y == j)
                {
                    spriteBullet.setPosition(sf::Vector2f(x, y));
                    window.draw(spriteBullet);
                    bullet_course.pop();
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
