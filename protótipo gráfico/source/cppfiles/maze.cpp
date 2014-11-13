#include "../maze.h"


Maze::Maze()
: matrix(NULL)
{
}


Maze::~Maze()
{
	if (matrix != NULL)
	{
		for (size_t i=0; i<_rows; i++)
		{
			delete[] matrix[i];
			matrix[i] = NULL;
		}
		
		delete[] matrix;
		matrix = NULL;
	}
}


void Maze::init(int n, int m)
{	
	if (matrix == NULL)
	{
		_rows = n; _cols = m;
		matrix = new Block*[_rows];
		for (size_t i=0; i<_rows; i++)
		{
			matrix[i] = new Block[_cols];
		}
	}
}


bool Maze::inited() const
{
	return matrix != NULL;
}


int Maze::rows() const
{
	return _rows;
}

int Maze::cols() const
{
	return _cols;
}


bool Maze::in_bounds(const Position& p) const
{
	return 0 <= p.x && p.x < _rows && 0 <= p.y && p.y < _cols;
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



Maze::_proxy Maze::operator[](int row)
{
	return _proxy(*this, row);
}

const Maze::_proxy Maze::operator[](int row) const
{
	return _proxy(*this, row);
}




// proxy class for operator[][]

Maze::_proxy::_proxy(Maze& _parent, int _row)
: parent(&_parent), const_parent(NULL), row(_row)
{
}

Maze::_proxy::_proxy(const Maze& _parent, int _row)
: const_parent(&_parent), parent(NULL), row(_row)
{
}

Block& Maze::_proxy::operator[](int col)
{
	return parent->matrix[row][col];
}

const Block& Maze::_proxy::operator[](int col) const
{
	return const_parent->matrix[row][col];
}

