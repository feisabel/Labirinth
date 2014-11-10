#include <iostream>
#ifndef _CLASSE_
#define _CLASSE_

enum{
	FILA, PILHA, DEQUE, LISTA
};

template <class tipo>
struct node{
	tipo info;
	node *prev, *next;
	node(){
		prev = NULL; next = NULL;
	}
};
//pilha, fila, lista duplamente encadeada, deque
template <class tipo>
class estruturaDeDados{
	node<tipo> *head;
	node<tipo> *topo;
	int tipo_da_classe;
	int tamanho;
public:	
	explicit estruturaDeDados(int t){
		tipo_da_classe = t;
		tamanho = 0;
		head = new node<tipo>;
		topo = head;
	}
	estruturaDeDados( estruturaDeDados &origem ){
		tipo_da_classe = origem.tipo_da_classe;
		tamanho = 0;
		head = new node<tipo>;
		topo = head;
		node<tipo> *aux = origem.head->next;
		while( aux != NULL ){
			push(aux->info);
			aux = aux->next;
		}
	}
	bool push(tipo); //fila e pilha
	bool pop(tipo&); //fila e pilha
	bool insere(tipo, int); //lista duplamente encadeada
	bool retira(tipo&, int); //lista duplamente encadeada
	bool pop_end(tipo&); //deque
	bool pop_begin(tipo&); //deque
	bool push_end(tipo); //deque
	bool push_begin(tipo); //deque
	void imprime();
	~estruturaDeDados(){
		tipo a;
		while(pop_end(a));
		delete head;
	}
};

#endif