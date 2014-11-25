#include "../classmain.h"
#include "../game.h"
#include "../scene_manager.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>


bool Main::quit = false;
// Essa sequência de variáveis estáticas que podem serão usadas no loop a seguir.
Game Main::game;
Menu Main::menu;
MenuContinue Main::menucontinue;
howToPlay Main::howtoplay;
EndGame Main::endgame;
Ranking Main::ranking;

void Main::loop ()
{
    // Este if testa se houve algum erro com a inicialização do jogo.
	if (!game.inited)
	{
		std::cerr << "Erro: não foi possível carregar jogo" << std::endl;
		return;
	}

    SceneManager::change_scene(menu);    // O ponteiro da cena passa a apontar para o menu.
    while (!quit)                        // Enquanto não receber quit válido, vai atualizar a cena.
    {
        SceneManager::redraw();
        SceneManager::update();
    }
    Scene::close();                      // Ao receber quit válido, fecha a cena.
}
