#ifndef __MAZE
#define __MAZE

#include "block.h"

class Maze
{
public:
	class _proxy;

	Maze(); 
	~Maze(); 

	void init(size_t n, size_t m); 
	bool inited() const;

	size_t rows() const;
	size_t cols() const;

    void maze_null() { matrix = NULL; }
	bool in_bounds(const Position&) const;

	Position& entrance();
	const Position& entrance() const;

	Position& exit();
	const Position& exit() const;

	_proxy operator[](size_t row);
	const _proxy operator[](size_t row) const;

private:
	size_t _rows;
	size_t _cols;

	Block **matrix;

	Position _entrance;
	Position _exit;
};


// proxy class for operator[][]
class Maze::_proxy
{
	friend class Maze;

public:
	Block& operator[](size_t row);
	const Block& operator[](size_t row) const;

private:
	_proxy(Maze& parent, size_t col);
	_proxy(const Maze& parent, size_t col);

    Maze* _parent;
    const Maze* _const_parent;
    size_t _col;
};


#endif
