#ifndef ITERATOR_H
#define ITERATOR_H

typedef struct _iterator *iterator;

/***********************************************
criaIterador - Criacao da instancia da estrutura associada a um iterador para uma lista ligada com n elementos.
Parametros:
	cabeça - endereco da copia da cabeça lista ligada a iterar
	cauda - endereco da copia da cauda lista ligada a iterar
	n - numero de elementos no vector
	mode - 0: front to back; 1: back to front
Retorno: apontador para a  instancia criada
Pre-condicoes:  head != NULL && tail != NULL && n > 0
***********************************************/
iterator new_iterator(node head, node tail, int n, int mode);

/***********************************************
destroiIterador - Liberta a memoria ocupada pela instancia da estrutura associada ao iterador.
Parametros:
	it - iterador a destruir
Retorno:
Pre-condicoes: it != NULL
***********************************************/
void destroy_iterator(iterator it);

/***********************************************
temSeguinteIterador - Indica se existe mais elementos para iterar no iterador.
Parametros:
	it - iterador
Retorno: 1 - caso exista mais elementos; 0 - caso contrario
Pre-condicoes: it != NULL
***********************************************/
int has_next_item(iterator it);

/***********************************************
seguinteIterador - Consulta o seguinte elemento no iterador.
Parametros:
	it - iterador
Retorno: enderco do elemento
Pre-condicoes: it != NULL && temSeguinteIterador(it) == 1
***********************************************/
void *next_item(iterator it);

#endif // ITERATOR_H
