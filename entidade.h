#include "lista.h"
#include "lista.hpp"
#include <cstdlib>

int randomica(int i, int j){
	int numero = rand()%(j-i+1);
	return i + numero;
}

struct posicao{
	int x;
	int y;
	posicao(): x(0), y(0){}
	posicao(int a, int b): x(a), y(b){}
};

class entidade{
protected:
	posicao pos;
public:
	entidade(): pos(0,0){}
	entidade(int a, int b): pos(a, b){}
	int getX(){ return pos.x; }
	int getY(){ return pos.y; }
	void setX(int a){ pos.x = a; }
	void setY(int a){ pos.y = a; }
};

class item : public entidade{
protected:
	int quantidade;
public:
	item(): quantidade( 0 ){}
	item(int a): quantidade( a ){} 
	int getQuantidade(){ return quantidade; }
	void setQuantidade(int a){ quantidade = a; }
};

class bloco : public entidade{
protected:	
	bool caminho; /*Se caminho true então é caminho e não é parede*/
	bool aceso; 							// Define se o bloco consta no FOV(field of vision) do player ou não
public:
	bloco(): caminho( false ), aceso( false ){}
	bool getCaminho(){ return caminho; }
	bool getAceso(){ return aceso; }
	void setCaminho(bool a){ caminho = a; }
	void setAceso(bool a){ aceso = a; }
};

class armadilha : public entidade {
protected:
	bool ativo;
public:
	armadilha(): ativo(true){}
};

class personagem : public entidade{
protected:	
	int pontos_vida;
	int velocidade;
public:
	personagem(): pontos_vida( 0 ), velocidade( 0 ){}
	void move(); 
	void tira_pontos();
	int getPontos_vida(){ return pontos_vida; }
	double getVelocidade(){ return velocidade; }
	void setPontos_vida(int a){ pontos_vida = a; }
	void setVelocidade(int a){ velocidade = a; }
};

class jogador : public personagem{
protected:	
	int municao;
public:
	jogador(): municao( 0 ) {}
	void marcar_caminho();
	void atirar();
	bool pegar_vida();
	bool pegar_municao();
	int getMunicao(){ return municao; }
	void setMunicao(int a){ municao = a; }
};

class monstro : public personagem{
public:
	bool perseguir();
};

class iluminacao{
public:
	int campo_visao;
	iluminacao(): campo_visao( 0 ){}
	bool atualiza();
	int getCampo_visao(){ return campo_visao; }
};


class tabuleiro{
public: 
	posicao dimencoes;
	bloco **matriz;
	posicao entrada;
	posicao saida;
	tabuleiro(): dimencoes( 0, 0 ), matriz( NULL ), entrada( 0, 0 ), saida( 0, 0 ){}
	void setDimencoes(int a, int b){ dimencoes.x = a; dimencoes.y = a; }
	void setEntrada(int a, int b){ entrada.x = a; entrada.y = b; }
	void setSaida(int a, int b){ saida.x = a; saida.y = b; }
};

class jogo{
protected:
	tabuleiro cena;
	jogador meu_jogador;
	estruturaDeDados<monstro> lista_monstro; //a definir
	estruturaDeDados<item> lista_municao; //a definir
	estruturaDeDados<item> lista_vida;
	estruturaDeDados<armadilha> lista_armadilha;
	estruturaDeDados<monstro> lista_spawn;
public:
	jogo(): lista_monstro( 0 ), lista_municao( 0 ), lista_vida( 0 ), lista_armadilha( 0 ), lista_spawn( 0 ) {}
	void loop(); /*onde o jogo acontece*/
	void recebe_jogadas();
	void andar();
	bool verifica_colisao();
	bool ativa_monstro();
	void inicializa( int **arquivo, posicao dimen );
};

/*função que forma o labririnto conforme as informações do arquivo de entrada e modifica entrada e saída*/
void jogo::inicializa( int **arquivo, posicao dimen ){
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
				cena.setEntrada(i, j);	
			if( arquivo[i][j] == 3 )
				cena.setSaida(i, j);
			if( arquivo[i][j] == 4 ){
				armadilha nova;
				nova.setX(i);
				nova.setY(j);
				lista_armadilha.push(nova);
			}
			if( arquivo[i][j] == 5 ){
				monstro novo;
				novo.setX(i);
				novo.setY(j);
				lista_spawn.push(novo);
			}
			if( arquivo[i][j] == 6 ){
				item vida(randomica(2, 4));
				lista_vida.push(vida); /*a quantidade é gerada randomicamente*/ 
			}
			if( arquivo[i][j] == 7 ){
				item muni(randomica(10, 15));
				lista_municao.push(muni); /*a quantidade é gerada randomicamente*/
			}
		} 
	}	
}

