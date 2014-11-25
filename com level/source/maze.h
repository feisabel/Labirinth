#ifndef __MAZE
#define __MAZE

#include "block.h"

/*		class Maze:
 *			A classe maze representa o mapa. As posições das entidades e dos outros objetos nele localizados são definidos por suas coordenadas.
 */

class Maze
{
public:
	class _proxy; // class para o operador [][]

	Maze();  // construtor
	~Maze(); // destruidor

	void init(size_t n, size_t m); // inicializa a matriz que define o maze
	bool inited() const; // define se já foi inicializada

	size_t rows() const; // construtor da variável da quantidade de linhas
	size_t cols() const; // construtor da variável da quantidade de colunas

    void maze_null() { matrix = NULL; } // faz a matriz apontar pra nulo
	bool in_bounds(const Position&) const; // verifica se a posição está dentro dos limites da matriz

	Position& entrance(); // construtor da entrada do labirinto
	const Position& entrance() const;

	Position& exit(); // construtor da saída do labirinto 
	const Position& exit() const;

	_proxy operator[](size_t row); // quantidade de linhas
	const _proxy operator[](size_t row) const;

private:
	size_t _rows;       // variável da quantidade de linhas
	size_t _cols;       // variável da quantidade de colunas

	Block **matrix;     // variável da matriz

	Position _entrance; // variável da entrada
	Position _exit;     // variável da saída
};


/* 	classe _proxy
		serve apenas como um meio de implementar o operador[] duplo para a matriz
*/

class Maze::_proxy
{
	friend class Maze;

public:
	Block& operator[](size_t row); 				// operator[] 
	const Block& operator[](size_t row) const;  // operator[] const

private:
	_proxy(Maze& parent, size_t col);			// construtor
	_proxy(const Maze& parent, size_t col);		// construtor

    Maze* _parent;					// ponteiro pra Maze
    const Maze* _const_parent;		// ponteiro pra const Maze
    size_t _col;					// número de cols
};


#endif
