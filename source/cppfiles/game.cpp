#include "../game.h"

// Função que forma o labririnto conforme as informações do arquivo de entrada e modifica entrance e exit
void Game::init()
{
	int i, j;
	cena.setDimencoes( dimen.x, dimen.y );
	cena.matriz = new bloco*[cena.dimencoes.x];
	for( i = 0; i < cena.dimencoes.x; i++ )
		cena.matriz[i] = new bloco[cena.dimencoes.y];
	for( i = 0; i < cena.dimencoes.x; i++ ){
		for( j = 0; j < cena.dimencoes.y; j++ ){
			if( arquivo[i][j] != 1 )
				cena.matriz[i][j].setCaminho(true);
			if( arquivo[i][j] == 2 )
				cena.setentrance(i, j);	
			if( arquivo[i][j] == 3 )
				cena.setSaida(i, j);
			if( arquivo[i][j] == 4 ){
				Trap nova;
				nova.setX(i);
				nova.setY(j);
				lista_Trap.push(nova);
			}
			if( arquivo[i][j] == 5 ){
				Enemy novo;
				novo.setX(i);
				novo.setY(j);
				lista_spawn.push(novo);
			}
			if( arquivo[i][j] == 6 ){
				item vida(randomica(2, 4));
				lista_vida.push(vida);    // A quantidade é gerada randomicamente.
			}
			if( arquivo[i][j] == 7 ){
				item muni(randomica(6, 18));
				lista__ammun.push(muni); // A quantidade é gerada randomicamente.
			}
			if( arquivo[i][j] == 8 ){
				Enemy novo;
				novo.setX(i);
				novo.setY(j);
				lista_Enemy.push(novo);
			}
		} 
	}	
}