#include "../maze.h"


Maze::Maze()
: matrix(NULL)
{
}


Maze::~Maze()
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


void Maze::init(size_t n, size_t m)
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


bool Maze::inited() const
{
	return matrix != NULL;
}


size_t Maze::rows() const
{
	return _rows;
}

size_t Maze::cols() const
{
	return _cols;
}


bool Maze::in_bounds(const Position& p) const
{
	return 0 <= p.x && p.x < _cols && 0 <= p.y && p.y < _rows;
}


Position& Maze::entrance()
{
	return _entrance;
}

const Position& Maze::entrance() const
{
	return _entrance;
}



Position& Maze::exit()
{
	return _exit;
}

const Position& Maze::exit() const
{
	return _exit;
}



Maze::_proxy Maze::operator[](size_t col)
{
	return _proxy(*this, col);
}

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

