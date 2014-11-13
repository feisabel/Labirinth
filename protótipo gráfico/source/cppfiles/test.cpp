#include "../enemy.h"
#include "../player.h"
#include "../game.h"

#include <unistd.h>
#include <cstdlib>
#include <iostream>

/*
int main(int argc, char const *argv[])
{
	system ("clear");

	Game game;

	if (!game.read_from_file()) {
		std::cout << "erro" << std::endl;
		return 1;
	}


	for (int i=0; i<game.maze.rows(); i++)
	{
		for (int j=0; j<game.maze.cols(); j++)
		{
			if (game.maze[i][j].type() == Block::WALL) std::cout << "█";
			else std::cout << " ";
		}

		std::cout << std::endl;
	}


	Player player;
	std::cin >> player.pos();

	Enemy enemy;
	std::cin >> enemy.pos();


	system("clear");

	for (int i=0; i<game.maze.rows(); i++)
	{
		for (int j=0; j<game.maze.cols(); j++)
		{
			if (game.maze[i][j].type() == Block::WALL) std::cout << "█";
			else
			{
				if (enemy.x() == i && enemy.y() == j) std::cout << "@";
				else if (player.x() == i && player.y() == j) std::cout << "&";
				else std::cout << " ";
			}
		}

		std::cout << std::endl;
	}

	usleep(600000);


	bool trial;
	do
	{
		system("clear");

		trial = enemy.chase(player, game.maze);

		for (int i=0; i<game.maze.rows(); i++)
		{
			for (int j=0; j<game.maze.cols(); j++)
			{
				if (game.maze[i][j].type() == Block::WALL) std::cout << "█";
				else
				{
					if (enemy.x() == i && enemy.y() == j) std::cout << "@";
					else if (player.x() == i && player.y() == j) std::cout << "&";
					else std::cout << " ";
				}
			}

			std::cout << std::endl;
		}

		usleep(300000);
	}
	while (trial);

	return 0;
}*/
