#include "source/game.h"

int main()
{
	Game game;
	
	if( !game.read_from_file() ) // Verificação de erro na entrada do arquivo.
		std::cout << "erro" << std::endl;
	
	// não implementado
	game.init();
	
	return 0;
}
