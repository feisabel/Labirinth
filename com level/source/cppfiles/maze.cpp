#include "../maze.h"


Maze::Maze() //construtor
: matrix(NULL)
{
}


Maze::~Maze() //destrutor
{
	if (matrix != NULL)
	{
		for (size_t i=0; i<_cols; i++)
		{
			delete[] matrix[i];
			matrix[i] = NULL;
		}
		
		delete[] matrix;
		matrix = NULL;
	}
}


void Maze::init(size_t n, size_t m) // inicializa a matriz de blocos dinamicamente
{	
	if (matrix == NULL)
	{
		_cols = n; _rows = m;
		matrix = new Block*[_cols];
		for (size_t i=0; i<_cols; i++)
		{
			matrix[i] = new Block[_rows];
		}
	}
}

// verifica se a matriz foi inicializada
bool Maze::inited() const
{
	return matrix != NULL;
}

// retorna a quantidade de linhas
size_t Maze::rows() const
{
	return _rows;
}

// retorna a quantidade de colunas
size_t Maze::cols() const
{
	return _cols;
}

// verifica se a posição está dento dos limites do labirinto
bool Maze::in_bounds(const Position& p) const
{
	return 0 <= p.x && p.x < _cols && 0 <= p.y && p.y < _rows;
}

// retorna entrada
Position& Maze::entrance()
{
	return _entrance;
}

// retorna entrada
const Position& Maze::entrance() const
{
	return _entrance;
}

// retorna saída
Position& Maze::exit()
{
	return _exit;
}

// retorna saída
const Position& Maze::exit() const
{
	return _exit;
}

// sobrecarga de operador []
Maze::_proxy Maze::operator[](size_t col)
{
	return _proxy(*this, col);
}

// sobrecarga de operador
const Maze::_proxy Maze::operator[](size_t col) const
{
	return _proxy(*this, col);
}




// proxy class for operator[][]

Maze::_proxy::_proxy(Maze& parent, size_t col)
: _parent(&parent), _const_parent(NULL), _col(col)
{
}

Maze::_proxy::_proxy(const Maze& parent, size_t col)
: _parent(NULL), _const_parent(&parent), _col(col)
{
}

Block& Maze::_proxy::operator[](size_t row)
{
	return _parent->matrix[_col][row];
}

const Block& Maze::_proxy::operator[](size_t row) const
{
	return _const_parent->matrix[_col][row];
}

