#ifndef __PLAYER
#define __PLAYER

#include "item.h"
#include "character.h"
#include <SFML/System/Clock.hpp>

// Classe Player com atributos e métodos necessários para o jogador

class Player : public Character
{
public:
	static const int max_ammo = 30; // Quantidade máxima de munição permitida
	static const int max_hp = 10; 	// Quantidade máxima de hp permitida

	// construtores
	Player(); // construtor padrão

	void p_start(); 	// Pega o tempo inicial quando o jogador entra no labirinto
	void p_end(); 		// Pega o tempo final
    int start();		// Get que retorna o valor do tempo inicial em segundos
    int end(); 			// Retorna o valor do tempo final em segundos

	int& ammo();	  	// Retorna a quantidade de munição
    int ammo() const; 	// Retorna a quantidade de munição (const)
    void ammo_fire(); 	// Diminui a quantidade de munição
    int& points(); 	  	// Retorna a quantidade de pontos do player

	Direction direction() const;  // Retorna a direção do player
	Direction& direction();		  // Retorna a direção do player

	bool can_see(const Entity& e); 	 // Verifica se o Entity está no campo de visão do player
    bool can_see(const Position& e); // Verifica se a Position está no campo de visão do player

	void get(Item i); 			// Pega um item e atualiza o hp do personagem ou a quantidade de munição conforme tipo

    void add_points(int a); 	// Recebe um valor para alterar a quantidade de pontos do player

private:
	static const unsigned fov = 4;

	sf::Clock clock; 	  // Declaração de clock para poder registrar os tempos do player
	sf::Time _start; 	  // Tipo de variável da biblioteca gráfica usada para os tempos, momento inicial
	sf::Time _end; 	 	  // Tipo de variável da biblioteca gráfica usada para os tempos, momento final
	int _ammo; 		 	  // Quantidade de munição
	int _points; 	 	  // Quantidade de pontos
	Direction _direction; // Direção do player
};


#endif
