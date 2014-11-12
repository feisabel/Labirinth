#include "../maze.h"


Maze::Maze(int n, int m)
: rows(n), cols(m)
{
	matrix = new Block*[n];
	for (int i=0; i<n; i++)
	{
		matrix[i] = Block[m];
	}
}


Maze::~Maze()
{
	for (int i=0; i<n; i++)
	{
		delete matrix[i];
	}
	delete matrix;
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

