#include "source/game.h"

int main()
{
	Game game;
	
	if( !Game.read_from_file() ) // Verificação de erro na entrada do arquivo.
		std::cout << "erro" << std::endl;
	
	// não implementado
	Game.init();
	
	return 0;
}
