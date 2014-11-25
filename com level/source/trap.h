#ifndef __TRAP
#define __TRAP

#include "entity.h"

/*
	classe Trap:
		Representa uma armadilha. Se o jogador se encontrar no mesmo bloco que ela enquanto ela estiver ativa, ele levará dano.
		Inimigos não sofrem danos de armadilhas.
*/

class Trap : public Entity
{
private:
	bool activated;  // variável booleana que define se a armadilha está ou não ativada

public:
	Trap(): activated(false) {} // construtor: inicia a armadilha como estando desativada

	bool is_active() { return activated; }    // método que retorna o estado da armadilha (ativada ou desativada)
	void activate() { activated = true; }     // ativa a armadilha
	void disactivate() { activated = false; } // desativa a armadilha
};


#endif
