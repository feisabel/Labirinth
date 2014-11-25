#ifndef __CHARACTER
#define __CHARACTER

#include "entity.h"

//classe Character representa os personagens do jogo: os monstros e o jogador

class Character : public Entity
{
protected:
	int _hp; //quantidade de hit points (vidas) que o personagem possui

public:
	Character(): _hp(5) {} //começa com 5 vidas

	void receive_dmg(int dmg) { _hp -= dmg; if (_hp < 0) _hp = 0; } //diminui a quantidade de vidas em um certo valor (dmg) recebido por parâmetro

	int hp() const { return _hp; } //retorna a quantidade de vidas

	int& hp() { return _hp; } //retorna a variável da quantidade de vidas
};


#endif
