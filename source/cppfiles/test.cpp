#include "../enemy.h"
#include "../player.h"
#include "../game.h"

int main(int argc, char const *argv[])
{	
	Game game;

	game.read_from_file();

	Player player;
	player.x() = 5;
	player.y() = 5;

	Enemy enemy;
	enemy.x() = 0;
	enemy.y() = 0;

	enemy.chase(player, game.maze);

	return 0;
}