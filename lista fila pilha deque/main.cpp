#include "lista.h"
#include "lista.hpp"

int main(){
	int a;
	estruturaDeDados<int> teste_fila(FILA);
	teste_fila.pop(a);
	teste_fila.push(4);
	teste_fila.push(3);
	teste_fila.imprime();
	estruturaDeDados<int> teste_novo = teste_fila;
	teste_novo.imprime();
	return 0;
}