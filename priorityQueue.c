#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "teams.h"

/*  Estrutura de dados do tipo de dados: dicionario ---> os elementos não podem ser repetidos com base num identificador (chave) dos elementos */
struct _pQueue
{
    team* vect;
	int actNElems;	
	int cap;
};

/* Prototipos das funcoes associadas a um dicionario */

/***********************************************
criaDicionario - Criacao da instancia da estrutura associada a um dicionario.
Parametros:
	 cap - capacidade prevista do dicionario
	 TipoChave – 0 – inteiro, 1 - string
Retorno: apontador para a  instancia criada
Pre-condicoes:
***********************************************/
pQueue newPQueue(int cap){
	pQueue pq;
	pq = (pQueue)malloc(sizeof(struct _pQueue));
	if (pq == NULL)
		return NULL;
	pq->cap = cap;
	pq->actNElems = 0;
	pq->vect = (team*)malloc(sizeof(team)*cap);
	return pq;
}

/***********************************************
destroiDicionario - Liberta a memoria ocupada pela instancia da estrutura associada ao dicionario.
Parametros:	d - dicionario a destruir
Retorno:
Pre-condicoes: d != NULL
***********************************************/
void destroyPQueue(pQueue pq){
	free(pq->vect);
	free(pq);
}

/***********************************************
DestroyPQueueAndElems - Liberta a memoria ocupada pela instancia da estrutura associada ao dicionario e os elementos.
Parametros:
	d - dicionario a destruir	destroi - função para destruição os elementos
Retorno:
Pre-condicoes: d != NULL
***********************************************/
void DestroyPQueueAndElems(pQueue pq, void (*destroi)(void *))
{       
	for(int i = 0; i < pq->cap; ++i)
		destroy_team(vect[i]);
	free(pq->vect);
	free(pq);
}

/***********************************************
adicionaElemDicionario - Adiciona o elemento dado no dicionario, se não existir um elemento com a mesma chave.
Parametros:
	d – dicionario
	ch - endereco da chave do elemento
	elem - endereco do elemento
Retorno: Retorna 1 se adicionar, e 0, caso contrário
Pre-condicoes: d != NULL
***********************************************/
int adicionaElemDicionario(pQueue pq, void *elem)
{
	int i,j;
	for(i = 0; i < cap; ++i){
		if(elem > pq->vect[i])
			
	}
}

/***********************************************
removeElemDicionario - Remove o elemento com a chave dada no dicionario, se existir.
Parametros:
	d – dicionario	ch – endereco da chave
Retorno: Retorna o elemento, caso exista ou NULL, caso contrario
Pre-condicoes: d != NULL
***********************************************/
void *removeElemDicionario(dicionario d, void *ch)
{
	tuplo t;
	node auxNo;
	int pos = dispersao(ch, d->tamanho, d->tipoCh);
	auxNo = d->elems[pos];
	if (auxNo == NULL)
		return 0;

	while (auxNo != NULL)
	{
		t = (tuplo)getElem(auxNo);
		if (!compChaves(ch, priTuplo(t), d->tipoCh))
		{
			if (prevNode(auxNo) == NULL)
				d->elems[pos] = nextNode(auxNo);
			else
				setNextNode(prevNode(auxNo), nextNode(auxNo));
			destroyNode(auxNo);
			void *elem = segTuplo(t);
			destroiTuplo(t);
			--d->numElems;
			return elem;
		}
		auxNo = nextNode(auxNo);
	}
	return NULL;
}

/***********************************************
iteradorDicionario - Cria e devolve um iterador para os elementos do dicionario.
Parametros:
	d - dicionario
Retorno: iterador do dicionario
Pre-condicoes: d != NULL && vazioDicionario(d)!=1
***********************************************/
iterador iteradorDicionario(dicionario d)
{
	void **vector = malloc(sizeof(void *) * d->numElems);
	node auxNo;
	tuplo t;
	int i = 0;
	for (int j = 0; i < d->numElems; ++j)
	{
		auxNo = d->elems[j];
		while (auxNo != NULL)
		{
			t = getElem(auxNo);
			vector[i] = segTuplo(t);
			auxNo = nextNode(auxNo);
			++i;
		}
	}

	return criaIterador(vector, d->numElems);
}

/***********************************************
iteradorChaveDicionario - Cria e devolve um iterador para as chaves dos elementos do dicionario.
Parametros:
	d - dicionario
Retorno: iterador do dicionario
Pre-condicoes: d != NULL && vazioDicionario(d)!=1
***********************************************/
iterador iteradorChaveDicionario(dicionario d)
{
	void **vector = malloc(sizeof(void *) * d->numElems);
	node auxNo;
	tuplo t;
	int i = 0;
	for (int j = 0; i < d->numElems; ++j)
	{
		auxNo = d->elems[j];
		while (auxNo != NULL)
		{
			t = getElem(auxNo);
			vector[i] = priTuplo(t);
			auxNo = nextNode(auxNo);
			++i;
		}
	}

	return criaIterador(vector, d->numElems);
}

int particioner(void** vector, int (*getValue)(void *), int R, int L){
	int RValue, LValue, P = (getValue(vector[R])+getValue(vector[L]))/2;
	while(R <= L){
		RValue = getValue(vector[R]);
		LValue = getValue(vector[L]);
		if(P <= RValue){
			--R;
			continue;
		}
		if(P > LValue){
			++L;
			continue;
		}
		void* aux = vector[R];
		vector[R] = vector[L];
		vector[L] = aux;
	}
	return R;
}

void merger(void** vector, int (*getValue)(void *), int R, int L){
	if(R <= L)
		return;
	int auxR = particioner(vector, getValue, R, L);
	merger(vector, getValue, auxR, L);
	merger(vector, getValue, R, ++auxR);
}

void **quickSort(dicionario dic, int (*getScore)(void *), int (*getBan)(void *), int (*getCertified)(void *))
{
	int banned, numElems;
	banned = 0;

	void **vector = malloc(sizeof(void *) * dic->numElems);
	node auxNo;
	tuplo t;
	int i = 0;
	for (int j = 0; i < dic->numElems; ++j)
	{
		auxNo = dic->elems[j];
		while (auxNo != NULL)
		{
			t = getElem(auxNo);
			if (getBan(segTuplo(t)))
			{
				++banned;
			}
			else
			{
				vector[i] = segTuplo(t);
			}
			auxNo = nextNode(auxNo);
			++i;
		}
	}

	numElems = dic->numElems - banned;
	merger(vector, getCertified, numElems, 0);
	merger(vector, getScore, numElems, 0);
	return vector;
}
