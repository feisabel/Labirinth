#ifndef __POSITION
#define __POSITION

#include "custom/list.h"
using custom::list;

#include <iostream>
#include <cmath>



/*	classe Position:
		representa uma posição em uma matriz bidimensional.
*/

struct Position
{
	int x;		// coordenada x
	int y;		// coordenada y

	// construtores
	Position ();			// construtor padrão
	Position (int, int);	// construtor que recebe dois inteiros

	// comparação
	bool operator== (const Position&) const; 	// compara duas posições; retorna true se têm as mesmas coordenadas, false caso contrário
	bool operator!= (const Position&) const;	// compara duas posições; retorna false se têm as mesmas coordenadas, true caso contrário
	bool adjacent_to (const Position&) const; 	// compara duas posições; retorna true caso a posição passada seja adjacente a essa, false caso contrário
	
	// operação
	int distance_to(const Position&) const;		// retorna a distância entre essa e outra posição 
};


// tipo Direction, representa uma direção
enum Direction {UP, DOWN, LEFT, RIGHT};


// retorna uma lista contendo as quatro posições adjacentes a pos
list<Position> get_adjacents(const Position& pos);		

// retorna a posição que se localiza na direção dir da posição pos 
Position get_adjacent(const Position& pos, const Direction& dir);


// imprime uma posição na saída padrão
std::ostream& operator<< (std::ostream&, const Position&);

// lê os dados de uma posição da entrada padrão
std::istream& operator>> (std::istream&, Position&);


#endif
