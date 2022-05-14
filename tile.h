#ifndef TILE_H
#define TILE_H

typedef struct _tile * tile;

/***********************************************
criaTalha - Criacao da instancia da estrutura associada a uma talha.
Parametros:
	treasoure - tesouro associado a uma telha
Retorno: apontador para a instancia criada
Pre-condicoes:
***********************************************/
tile new_tile(int treasure);

/***********************************************
destroiTalha - Liberta a memoria ocupada pela instancia da estrutura associada a talha.
Parametros:
	t - talha a destruir
Retorno:
Pre-condicoes: t != NULL
***********************************************/
void destroy_tile(tile t);

/***********************************************
devolceTesouro - vai buscar o tesouro da talha.
Parametros:
	t - talha
Retorno: devolve o tesouro associado a talha
Pre-condicoes:  t != NULL
***********************************************/
int get_treasure(tile t);

/***********************************************
devolceEscavado - vai buscar o o numero de vezes que a talha foi escavada.
Parametros:
	t - talha
Retorno: devolve o numero de vezes que a talha foi escavada
Pre-condicoes:  t != NULL
***********************************************/
int get_excavated(tile t);

/***********************************************
incEsavado - incrementa o numero de vezes que a talha foi escavada.
Parametros:
	t - talha
Retorno: um array de dois inteiros com o tesouro associado a talha na primeira posição e numero de vezes que a talha foi escava na segunda
Pre-condicoes:  t != NULL
***********************************************/
int* inc_excaveted(tile t);

#endif