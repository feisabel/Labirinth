#include "entidade.h"
#include "lista.h"
#include "lista.hpp"
#include <fstream>

bool leitura_arquivo(posicao &dimen, int **&meu_arquivo){
	int a, b, i, j;
	std::ifstream entrada; /*Conexão com o arquivo "entrada.txt"*/
	entrada.open ( "entrada.txt", std::ifstream::in ); /*Abre o arquivo "entrada.txt"*/
	if( entrada.is_open() ){
		if( !(entrada >> a) ){ return false; }
		if( !(entrada >> b) ){ return false; }
		meu_arquivo = new int*[a];
		for( i = 0; i < a; i++ )
			meu_arquivo[i] = new int[b];
		for( i = 0, j = 0; i < a && ( entrada >> meu_arquivo[i][j] ); ){
            if( j == b-1 ){ 
                i++;
                j = 0;
            }
            else
                j++;
        }
        dimen.x = a;
        dimen.y = b;
        /*verifica se a leitura da matriz ocorreu corretamente*/
        if( i != a || j != 0 )
        	return false;
	}
	else
		return false;

	return true;
}

int main(){
	jogo meu_jogo;
	posicao dimen;
	int **arquivo;
	tabuleiro meu_tabuleiro;
	if(!(leitura_arquivo(dimen, arquivo))) /*Verificação de erro na entrada do arquivo*/
		std::cout << "erro" << std::endl;
	meu_jogo.inicializa(arquivo, dimen);
	return 0;
}
