#ifndef __CLASSMAIN
#define __CLASSMAIN

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "menu.h"
#include "game.h"
#include "menucontinue.h"
#include "howtoplay.h"
#include "endgame.h"
#include "ranking.h"

class Main
{
public:
	static Menu menu;
	static Game game;
    static MenuContinue menucontinue;
	static howToPlay howtoplay;
	static EndGame endgame;
	static Ranking ranking;
	static bool quit;

    Main() {}

    void loop();
};

#endif
