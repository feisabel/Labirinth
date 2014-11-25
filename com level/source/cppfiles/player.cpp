#include "../player.h"

// construtor padrão
Player::Player()
: _ammo(14), _points(0)
{
	_hp = max_hp;
}


// Pega o tempo inicial quando o jogador entra no labirinto
void Player::p_start()
{
	_start = clock.getElapsedTime();
}

// Pega o tempo final
void Player::p_end()
{
	_end = clock.getElapsedTime();
} 


// Get que retorna o valor do tempo inicial em segundos
int Player::start()
{
	return _start.asSeconds();
} 

// Get que retorna o valor do tempo final em segundos
int Player::end()
{
	return _end.asSeconds();
} 				


// Retorna a quantidade de munição
int Player::ammo() const
{
	return _ammo;
} 

// Retorna a quantidade de munição
int& Player::ammo()
{
	return _ammo;
}


// Diminui a quantidade de munição
void Player::ammo_fire()
{
	_ammo--;
} 

// Retorna a quantidade de pontos do player
int& Player::points()
{
	return _points;
} 


// Retorna a direção do player
Direction Player::direction() const
{
	return _direction;
} 

// Retorna a direção do player
Direction& Player::direction()
{
	return _direction;
}


// Verifica se o Entity está no campo de visão do player
bool Player::can_see(const Entity& e)
{
	return _pos.x-fov <= e.x() && e.x() <= _pos.x+fov && _pos.y-fov <= e.y() && e.y() <= _pos.y+fov;
}

// Verifica se a Position está no campo de visão do player
bool Player::can_see(const Position& e) 
{
	return (_pos.x-fov <= e.x) && (e.x <= _pos.x+fov) && (_pos.y-fov <= e.y) && (e.y <= _pos.y+fov);
}


// Recebe um valor para alterar a quantidade de pontos do player
void Player::add_points(int a)
{
    _points += a;
}

 // Pega um item e atualiza o hp do personagem ou a quantidade de munição conforme tipo
void Player::get(Item i)
{
	if (i.type() == Item::HEAL)
	{
		_hp += i.amount();
		if (_hp > max_hp) _hp = max_hp;
	}
	else
	{
		_ammo += i.amount();
		if (_ammo > max_ammo) _ammo = max_ammo;
	}
}