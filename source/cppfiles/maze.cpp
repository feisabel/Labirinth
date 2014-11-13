#include "../maze.h"


Maze::Maze()
: _inited(false)
{
}


Maze::~Maze()
{
	if (_inited)
	{
		for (int i=0; i<_rows; i++)
		{
			delete matrix[i];
		}
		
		delete matrix;

		_inited = false;
	}
}


void Maze::init(int n, int m)
{	
	if (!_inited)
	{
		_rows = n; _cols = n;
		matrix = new Block*[_rows];
		for (int i=0; i<_rows; i++)
		{
			matrix[i] = new Block[_cols];
		}

		_inited = true;
	}
}


bool Maze::inited() const
{
	return _inited;
}


int Maze::rows() const
{
	return _rows;
}

int Maze::cols() const
{
	return _cols;
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

