#ifndef __PLAYER
#define __PLAYER

#include "item.h"
#include "character.h"
#include <SFML/System/Clock.hpp>

//Classe Player com atributos e métodos necessários para o jogador
class Player : public Character
{
public:
	static const int max_ammo = 30; //Quantidade máxima de munição permitida
	static const int max_hp = 10; //Quantidade máxima de hp permitida

private:
	static const unsigned fov = 4;

	sf::Clock clock; //Declaração de clock para poder registrar os tempos do player
	sf::Time _start; //Tipo de variável da biblioteca gráfica usada para os tempos, momento inicial
	sf::Time _end; //Tipo de variável da biblioteca gráfica usada para os tempos, momento final
	int _ammo; //Quantidade de munição
	int _points; //Quantidade de pontos
	Direction _direction; //Direção do player

public:
	Player() : _ammo(14), _points(0) { _hp = max_hp; }

	void p_start(){ _start = clock.getElapsedTime(); }//Método que pega o tempo inicial quando o jogador entra no labirinto
	void p_end(){ _end = clock.getElapsedTime(); } //Método que pega o tempo final
    int start(){ return _start.asSeconds(); } //Método get que retorna o valor do tempo inicial em segundos
    int end(){ return _end.asSeconds(); } //Método get que retorna o valor do tempo final em segundos

	void get(Item i) //Método que pega um item e atualiza o hp do personagem ou a quantidade de munição conforme tipo
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

	int ammo() const { return _ammo; } //Método que retorna a quantidade de munição
	int& ammo() { return _ammo; } //Método que retorna a quantidade de munição
    void ammo_fire() { _ammo--; } //Método que diminui a quantidade de munição
    int& points() { return _points; } //Método que retorna a quantidade de pontos do player

	Direction direction() const { return _direction; } //Método que retorna a direção do player
	Direction& direction() { return _direction; } //Método que retorna a direção do player

	bool can_see(const Entity& e) //Verifica se o Entity está no campo de visão do player
	{
		return _pos.x-4 <= e.x() && e.x() <= _pos.x+4 && _pos.y-4 <= e.y() && e.y() <= _pos.y+4;
	}

    bool can_see(const Position& e) //Verifica se a Position está no campo de visão do player
	{
		return (_pos.x-4 <= e.x) && (e.x <= _pos.x+4) && (_pos.y-4 <= e.y) && (e.y <= _pos.y+4);
	}

    void add_points(int a) //Recebe um valor para alterar a quantidade de pontos do player
    {
        _points+= a;
    }
};


#endif
