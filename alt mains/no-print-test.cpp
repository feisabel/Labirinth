#include "../source/enemy.h"
#include "../source/player.h"
#include "../source/game.h"

#include <unistd.h>
#include <cstdlib>
#include <iostream>


int main(int argc, char const *argv[])
{	
	Game game;

	Player player;
	std::cin >> player.pos();

	Enemy enemy;
	std::cin >> enemy.pos();

	bool trial;
	do
	{
		trial = enemy.chase(player, game.maze);
	}
	while (trial);

	return 0;
}