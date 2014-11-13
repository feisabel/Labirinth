#include "../game.h"
#include <fstream>
#include <iostream>

// Função que forma o labririnto conforme as informações do arquivo de entrada e modifica entrance e exit
bool Game::read_from_file()
{
	std::ifstream entrada; 							   // Conexão com o arquivo "entrada.txt".
	
	entrada.open ( "source/cppfiles/entrada.txt", std::ifstream::in ); // Abre o arquivo "entrada.txt".
	
	if( entrada.is_open() ) {
		int a, b;
		
		if( !(entrada >> a) ) { std::cout << "não leu a" << std::endl; return false; }
		if( !(entrada >> b) ) { std::cout << "não leu a" << std::endl; return false; }
		
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
        	return false;
        }
	}
	else {
		std::cout << "não abriu arquivo" << std::endl;
		return false;
	}

	return true;
}