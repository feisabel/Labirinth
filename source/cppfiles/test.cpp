#include "../enemy.h"
#include "../player.h"
#include "../game.h"
#include <iostream>

int main(int argc, char const *argv[])
{	
	Game game;

	if (!game.read_from_file())
		std::cout << "erro" << std::endl;

	Player player;
	player.pos() = Position(1, 1);

	Enemy enemy;
	enemy.pos() = Position(1, 4);

	enemy.chase(player, game.maze);

	return 0;
}