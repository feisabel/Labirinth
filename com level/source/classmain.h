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

/*
	classe Main:
		Objeto que define o jogo em si.
		Aqui encontram-se as variáveis estáticas dos objetos principais para o jogo, juntamente com o loop de atualização
*/

class Main
{
public:
	static Menu menu;                  // variável estática do menu principal
	static Game game;                  // variável estática do jogo
    static MenuContinue menucontinue;  // variável estática do menu de pausa
	static howToPlay howtoplay;        // variável estática do how to play
	static EndGame endgame;		       // variável estática do fim do jogo
	static Ranking ranking;            // variável estática do ranking
	static bool quit;                  // variável booleana que define o fechamento do jogo

    Main() {}

    void loop();  // loop de atualização
};

#endif
