#ifndef __TRAP
#define __TRAP

/*		class Trap:
 *			Representa uma armadilha. Caso o jogador se encontre em cima de um FLOOR com TRAP ativa, ele levará dano.        
 *			Inimigos não levam dano de armadilhas.
 */

#include "entity.h"

class Trap : public Entity
{
private:
	bool activated; // varíável booleana que define se a armadilha se encontra ativa naquele instante ou não

public:
	Trap(): activated(false) {} // construtor que inicial a armadilha como desativada

	bool is_active() { return activated; }     // método que retorna o estado da armadilha (ativada ou desativada)
	void activate() { activated = true; }      // ativa a armadilha
	void disactivate() { activated = false; }  // desativa a armadilha
};


#endif
