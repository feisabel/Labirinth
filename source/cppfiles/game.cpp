#include "../game.h"

// Função que forma o labririnto conforme as informações do arquivo de entrada e modifica entrance e exit
void Game::init()
{
	// implementar	
}


bool Game::read_from_file()
{
	std::ifstream entrada; 							   // Conexão com o arquivo "entrada.txt".
	
	entrada.open ( "entrada.txt", std::ifstream::in ); // Abre o arquivo "entrada.txt".
	
	if( entrada.is_open() ){
		int a, b;
		
		if( !(entrada >> a) ) { return false; }
		if( !(entrada >> b) ) { return false; }
		
		maze.init(a, b);
		
		for (int i=0; i<a; i++)
		{
			for (int j=0; j<b; j++)
			{
				int x;
				entrada >> x;

				if (x == 1) maze[i][j].type = WALL; break;
				else
				{
					maze[i][j].type == FLOOR;

					if (x == 2) maze.entrance() = Position(i, j);
					else if (x == 3) maze.exit() = Position(i, j);
					else if (x == 4)
					{
						traps.push_back(Trap());
						traps.back().pos = Position(i, j);
					}
					else if (x == 5)
					{
						spawns.push_back(Spawn());
						spawns.back().pos = Position(i, j);
					}
					else if (x == 6)
					{
						hearts.push_back(Item());
						hearts.back().pos = Position(i, j);
					}
					else if (x == 7)
					{
						ammuns.push_back(Item());
						ammuns.back().pos = Position(i, j);
					}
					else if (x == 8)
					{
						enemies.push_back(Enemy());
						enemies.back().pos = Position(i, j);
					}
				}
			}
		}
        // Verifica se a leitura da matriz ocorreu corretamente.
        if( i != a )
        	return false;
	}
	else
		return false;

	return true;
}