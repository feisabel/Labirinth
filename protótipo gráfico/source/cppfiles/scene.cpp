#include "../scene.h"

sf::RenderWindow Scene::window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "Labirinto");

void Scene::close()
{
	window.close();
}