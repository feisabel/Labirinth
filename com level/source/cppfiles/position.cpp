#include "../position.h"

// construtores

// construtor padrão
Position::Position ()
: x(0), y(0)
{
}

// construtor com dois inteiros
Position::Position (int a, int b)
: x(a), y(b)
{	
}


// comparação

// compara duas posições; retorna true se tiverem as mesmas coordenadas, false caso contrário
bool Position::operator== (const Position& other) const
{
	return other.x == x && other.y == y;
}


// compara duas posições; retorna false se tiverem as mesmas coordenadas, true caso contrário
bool Position::operator!= (const Position& other) const
{
	return !operator==(other);
}

// compara duas posições; retorna true se forem adjacentes, false caso contrário
bool Position::adjacent_to (const Position& other) const
{
	return ( x == other.x && y == other.y + 1 )
		|| ( x == other.x && y == other.y - 1 )
		|| ( y == other.y && x == other.x + 1 )
		|| ( y == other.y && x == other.x - 1 );
}


int Position::distance_to(const Position& other) const
{
	return sqrt(pow((other.x - x), 2) + pow((other.y - y), 2));
}



list<Position> get_adjacents(const Position& p)
{
	list<Position> tmp;

	int deltaX[4] = {-1, 0, 1, 0};
	int deltaY[4] = { 0, 1, 0,-1};

	for (int i=0; i<4; i++)
	{
		tmp.push_back(Position(p.x + deltaX[i], p.y + deltaY[i]));
	}

	return tmp;
}


Position get_adjacent(const Position& p, const Direction& d)
{
	    if(d == UP)
            return Position(p.x, p.y-1);
		if(d == DOWN)
            return Position(p.x, p.y+1);
		if(d == LEFT)
            return Position(p.x-1, p.y);
		if(d == RIGHT)
            return Position(p.x+1, p.y);

}


std::ostream& operator<< (std::ostream& out, const Position& p)
{
	return out << "(" << p.x << ", " << p.y << ")";
}

std::istream& operator>> (std::istream& in, Position& p)
{
	return in >> p.x >> p.y;
}

