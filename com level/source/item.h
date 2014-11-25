#ifndef __ITEM
#define __ITEM

#include "entity.h"
#include "random.h"

//classe Item representa os itens que o jogador pode adquirir: munição e cura

class Item : public Entity
{
public:
	enum Type {HEAL, AMMO}; //tipos de itens: cura (HEAL) e munição (AMMO)
protected:
	int _amount; //quantidade
	Type _type; //variável que determina o tipo do item

public:
	Item() { _amount = randomize(5, 10); } //construtor padrão que inicializa a quantidade com um valor aleatório entre 5 e 10
	Item(Type t) : _type(t) { _amount = randomize(5, 10); } //construtor que recebe como parâmetro o tipo do item e inicializa a quantidade com um valor aleatório entre 5 e 10
	Item(Type t, int a) : _amount(a), _type(t) {} // construtor que recebe como parâmetros o tipo do item e a sua quantidade

	int& amount() { return _amount; } // retorna a variável da quantidade
	int amount() const { return _amount; } // retorna a quantidade
	Type& type() { return _type; } // retorna a variável do tipo
	Type type() const { return _type; } // retorna o tipo
};

#endif
