#ifndef __MAZE
#define __MAZE

#include "block.h"

class Maze
{
public:
	class _proxy;

	Maze();
	~Maze();

	void init(int n, int m);
	bool inited() const;

	int rows() const;
	int cols() const;

	Position& entrance();
	const Position& entrance() const;
	
	Position& exit();
	const Position& exit() const;

	_proxy& operator[](int row);
	const _proxy& operator[](int row) const;

private:
	int rows;
	int cols;

	bool _init;

	Block *matrix;

	Position _entrance;
	Position _exit;
};


// proxy class for operator[][]
class Maze::_proxy
{
	friend class Maze;

public:
	int& operator[](int col);
	int operator[](int col) const;

private:
	_proxy(Maze &_parent, int _row);

    Maze& parent;
    int row;
};


#endif