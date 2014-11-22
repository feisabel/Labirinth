#include "../classmain.h"
#include "../game.h"
#include "../scene_manager.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>


bool Main::quit = false;

Game Main::game;
Menu Main::menu;
MenuContinue Main::menucontinue;
howToPlay Main::howtoplay;
EndGame Main::endgame;
Ranking Main::ranking;

void Main::loop ()
{
    SceneManager::change_scene(menu);
    while (!quit)
    {
        SceneManager::redraw();
        SceneManager::update();
    }
    Scene::close();
}
