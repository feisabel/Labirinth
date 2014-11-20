#ifndef __CLASSMAIN
#define __CLASSMAIN

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "menu.h"
#include "game.h"
#include "menucontinue.h"

class Main
{
public:
	static Menu menu;
	static Game game;
    static MenuContinue menucontinue;
	static bool quit;

    Main() {}

    void loop();
};

#endif
