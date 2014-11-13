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

	_proxy operator[](int row);
	const _proxy operator[](int row) const;

private:
	int _rows;
	int _cols;

	bool _inited;

	Block **matrix;

	Position _entrance;
	Position _exit;
};


// proxy class for operator[][]
class Maze::_proxy
{
	friend class Maze;

public:
	Block& operator[](int col);
	const Block& operator[](int col) const;

private:
	_proxy(Maze& _parent, int _row);
	_proxy(const Maze& _parent, int _row);

    Maze* parent;
    const Maze* const_parent;
    int row;
};


#endif