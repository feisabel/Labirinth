#include "../maze.h"


Maze::Maze()
: inited(false)
{
}


Maze::~Maze()
{
	if (inited)
	{
		for (int i=0; i<_rows; i++)
		{
			delete matrix[i];
		}
		
		delete matrix;

		inited = false;
	}
}


Maze::init(int n, int m)
{	
	if (!inited)
	{
		_rows = n; _cols = n;
		matrix = new Block*[_rows];
		for (int i=0; i<_rows; i++)
		{
			matrix[i] = Block[_cols];
		}

		inited = true;
	}
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



_proxy& Maze::operator[](int row)
{
	return _proxy(*this, row);
}

const _proxy& Maze::operator[](int row) const
{
	return _proxy(*this, row);
}




// proxy class for operator[][]

_proxy(Maze &_parent, int _row)
: parent(_parent), row(_row)
{
}

int& Maze::_proxy::operator[](int col)
{
	return parent.matrix[row][col];
}

int Maze::_proxy::operator[](int col) const
{
	return parent.matrix[row][col];
}

