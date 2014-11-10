#include "lista.h"
#ifndef _CLASSE_HPP_
#define _CLASSE_HPP_
//as listas têm cabeça

//fila e pilha
template <class tipo>
bool estruturaDeDados<tipo>::push(tipo novo){
	return push_end(novo);
}

//fila e pilha
template <class tipo>
bool estruturaDeDados<tipo>::pop(tipo&a){
	if(tipo_da_classe == FILA)
		return pop_begin(a);
	else
		return pop_end(a);
}

//lista duplamente encadeada
//posicao começando de 0
template <class tipo>
bool estruturaDeDados<tipo>::insere(tipo novo, int p){
	if(p > tamanho)
		return false;
	else{
		node<tipo> *aux = new node<tipo>;
		aux->info = novo;
		if(head->next == NULL){
			head->next = aux;
			aux->prev = head;
		}
		else{
			node<tipo> *aux2 = head;
			while(p != 0){
				aux2 = aux2->next;
				p--;
			}
			aux->next = aux2->next;
			if(aux2->next != NULL)
				aux2->next->prev = aux;
			aux->prev = aux2;
			aux2->next = aux;
		}		
		tamanho++;
		return true;
	}
}

//lista duplamente encadeada
//posicao começando de 0
template <class tipo>
bool estruturaDeDados<tipo>::retira(tipo &a, int p){
	if(p >= tamanho || tamanho == 0)
		return false;
	else{
		node<tipo> *aux = head, *aux2;
		while(p != 0){
			aux = aux->next;
			p--;
		}
		aux2 = aux->next;
		aux->next = aux2->next;
		aux2->prev = aux;
		a = aux2->info;
		tamanho--;
		if(tamanho == 0)
			head->next = NULL;
		delete aux2;
		return true;
	}
} 

//deque
template <class tipo>
bool estruturaDeDados<tipo>::pop_end(tipo &a){
	if(topo != head){
		node<tipo> *aux = topo;
		a = topo->info;
		topo = topo->prev;
		delete aux;
		if(topo != NULL)
			topo->next = NULL;
		tamanho--;
		return true;
	}
	return false;
}

//deque
template <class tipo>
bool estruturaDeDados<tipo>::pop_begin(tipo &a){
	if(head->next != NULL){
		node<tipo> *aux = head->next;
		a = aux->info;
		head->next = aux->next;
		aux->prev = head;
		tamanho--;
		delete aux;
		return true;
	}
	return false;
} 

//deque
template <class tipo>
bool estruturaDeDados<tipo>::push_end(tipo novo){
	node<tipo> *aux = new node<tipo>;
	aux->info = novo;
	if(topo != head){
		tamanho++;
		topo->next = aux;
		aux->prev = topo;
		topo = aux;
		return true;
	}
	else{
		tamanho++;
		head->next = aux;
		aux->prev = head;
		topo = aux;
		return true;	}
	return false;
}

//deque
template <class tipo>
bool estruturaDeDados<tipo>::push_begin(tipo novo){
	node<tipo> *aux = new node<tipo>;
	aux->info = novo;
	if(head != topo){
		tamanho++;
		aux->next = head->next;
		if(head->next != NULL)
			head->next->prev = aux;
		aux->prev = head;
		head->next = aux;
		return true;
	}
	else{
		tamanho++;
		head->next = aux;
		aux->prev = head;
		topo = aux;
		return true;
	}
	return false;
}

template <class tipo>
void estruturaDeDados<tipo>::imprime(){
	node<tipo> *aux = head->next;
	while(aux != NULL){
		std::cout << aux->info << " ";
		aux = aux->next;
	}
	std::cout << std::endl;
}


#endif