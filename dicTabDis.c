#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "chaves.h"
#include "tuplo.h"
#include "iterador.h"
#include "node.h"
#include "dicionario.h"

/*  Estrutura de dados do tipo de dados: dicionario ---> os elementos não podem ser repetidos com base num identificador (chave) dos elementos */
struct _dicionario
{
	node *elems; // apontador para vector de noSimples (lista com cabeça)
	int numElems;
	int capacidade; // capacidade prevista
	int tamanho;	// tamanho do vector criado
	int tipoCh;		// 0-inteiro; 1-string
};

/* Prototipos das funcoes associadas a um dicionario */

/* função auxiliar para calcular o primo maior que n */

int is_prime(int n)
{
	if (n == 0 || n == 1 || (n % 2 == 0 && n > 2))
		return 0;

	else
	{
		for (int i = 3; i <= sqrt(n); ++i)
			if ((n % i) == 0)
				return 0;
		return 1;
	}
	return 0;
}

int primo(int n)
{
	int isPrime = 0;
	for (; !isPrime; ++n)
		isPrime = is_prime(n);
	return n - 1;
}

/***********************************************
criaDicionario - Criacao da instancia da estrutura associada a um dicionario.
Parametros:
	 cap - capacidade prevista do dicionario
	 TipoChave – 0 – inteiro, 1 - string
Retorno: apontador para a  instancia criada
Pre-condicoes:
***********************************************/
dicionario criaDicionario(int cap, int tipoChave)
{
	dicionario d;
	int i;
	d = (dicionario)malloc(sizeof(struct _dicionario));
	if (d == NULL)
		return NULL;
	d->tamanho = primo(2 * cap);
	d->elems = (node *)malloc(sizeof(node) * d->tamanho);
	if (d->elems == NULL)
	{
		free(d);
		return NULL;
	}
	for (i = 0; i < d->tamanho; i++)
		d->elems[i] = NULL;
	d->numElems = 0;
	d->capacidade = cap;
	d->tipoCh = tipoChave;
	return d;
}

/***********************************************
destroiDicionario - Liberta a memoria ocupada pela instancia da estrutura associada ao dicionario.
Parametros:	d - dicionario a destruir
Retorno:
Pre-condicoes: d != NULL
***********************************************/
void destroiDicionario(dicionario d)
{
	int i = 0;
	node aux;
	tuplo t;
	for (; i < d->tamanho; i++)
	{
		aux = d->elems[i];
		while (aux != NULL)
		{
			d->elems[i] = nextNode(aux);
			t = (tuplo)getElem(aux);
			destroyNode(aux);
			destroiTuplo(t);
			aux = d->elems[i];
		}
	}
	free(d->elems);
	free(d);
}

/***********************************************
destroiDicEElems - Liberta a memoria ocupada pela instancia da estrutura associada ao dicionario e os elementos.
Parametros:
	d - dicionario a destruir	destroi - função para destruição os elementos
Retorno:
Pre-condicoes: d != NULL
***********************************************/
void destroiDicEElems(dicionario d, void (*destroi)(void *))
{
	int i = 0;
	node aux;
	tuplo t;
	for (; i < d->tamanho; i++)
	{
		aux = d->elems[i];
		while (aux != NULL)
		{
			d->elems[i] = nextNode(aux);
			t = getElem(aux);
			destroi(segTuplo(t));
			destroyNode(aux);
			destroiTuplo(t);
			aux = d->elems[i];
		}
	}
	free(d->elems);
	free(d);
}

/***********************************************
vazioDicionario - Indica se o dicionario está vazio.
Parametros:
	d - dicionario
Retorno: 1- caso dicionario vazio; 0 - caso contrário
Pre-condicoes: d != NULL
***********************************************/
int vazioDicionario(dicionario d)
{
	if (d->numElems == 0)
		return 1;
	return 0;
}

/***********************************************
tamanhoDicionario - Consulta o numero de elementos no dicionario.
Parametros:
	d - dicionario
Retorno: numero de elementos no dicionario
Pre-condicoes: d != NULL
***********************************************/
int tamanhoDicionario(dicionario d)
{
	return d->numElems;
}
/***********************************************
existeElemDicionario – Indica se o elemento  com a chave dada existe no dicionario.
Parametros:
	d – dicionario
	ch – endereço da chave do elemento
Retorno: retorna 1 se existir, e 0, caso contrário
Pre-condicoes: d != NULL
***********************************************/
int existeElemDicionario(dicionario d, void *ch)
{
	if (elementoDicionario(d, ch) != NULL)
		return 1;
	return 0;
}

/***********************************************
elementoDicionario - retorna o elemento no dicionario com a chave dada
Parametros:
	d – dicionario	ch - endereco da chave do elemento
Retorno: retorna o elemento
Pre-condicoes: d != NULL
***********************************************/
void *elementoDicionario(dicionario d, void *ch)
{
	tuplo t;
	node auxNo;
	int pos = dispersao(ch, d->tamanho, d->tipoCh);
	auxNo = d->elems[pos];
	while (auxNo != NULL)
	{
		t = getElem(auxNo);
		if (igualChaves(priTuplo(t), ch, d->tipoCh) == 1)
			return segTuplo(t);
		auxNo = nextNode(auxNo);
	}
	return NULL;
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
int adicionaElemDicionario(dicionario d, void *ch, void *elem)
{
	int pos;
	node auxNo;
	if (existeElemDicionario(d, ch) == 1)
		return 0;
	pos = dispersao(ch, d->tamanho, d->tipoCh);

	tuplo t = criaTuplo(d->tipoCh, ch, elem);

	if (d->elems[pos] == NULL)
	{
		auxNo = newNode(t);
		setNextNode(auxNo, NULL);
		setPrevNode(auxNo, NULL);
	}
	else
	{
		auxNo = newNode(t);
		setNextNode(auxNo, d->elems[pos]);
		setPrevNode(d->elems[pos], auxNo);
	}
	d->elems[pos] = auxNo;
	d->numElems++;
	return 1;
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

int particioner(void **vector, int (*getValue)(void *), int R, int L)
{

	int LVal, i = L, P = getValue(vector[R]);

	if (L == R - 1)
	{
		if (getValue(vector[L]) > P)
		{
			void *aux = vector[L];
			vector[L] = vector[R];
			vector[R] = aux;
		}
		return L;
	}

	while (L != R - 1)
	{
		LVal = getValue(vector[L]);
		if (LVal > P)
		{
			for (; getValue(vector[i]) > P && i < R; i++)
				;
			void *aux = vector[L];
			vector[L] = vector[i];
			vector[i] = aux;
			if (i == R - 1)
			{
				++L;
				++i;
				aux = vector[L];
				vector[L] = vector[i];
				vector[i] = aux;
				break;
			}
		}
		++L;
	}
	return L;
}

int strSum(char *str)
{
	int bucket = 0;
	for (int i = 0; str[i] != '\0'; ++i)
	{
		bucket += str[i];
	}
	return bucket;
}

int strParticioner(void **vector, int R, int L, int *aux)
{
	int LVal, i = L, P = aux[R];
	if (L == R - 1)
	{
		if (aux[L] > P)
		{
			aux[R] = aux[L];
			aux[L] = P;
			void *temp = vector[L];
			vector[L] = vector[R];
			vector[R] = temp;
		}
		return L;
	}

	while (L != R - 1)
	{
		LVal = aux[L];
		if (LVal > P)
		{
			for (; aux[i] > P && i < R; i++)
				;
			int temp1 = aux[L];
			aux[L] = aux[i];
			aux[i] = temp1;
			void *temp2 = vector[L];
			vector[L] = vector[i];
			vector[i] = temp2;
			if (i == R - 1)
			{
				++L;
				++i;
				temp1 = aux[L];
				aux[L] = aux[i];
				aux[i] = temp1;
				temp2 = vector[L];
				vector[L] = vector[i];
				vector[i] = temp2;
				break;
			}
		}
		++L;
	}
	return L;
}

void merger(void **vector, int (*getValue)(void *), int R, int L)
{
	if (R <= L)
		return;

	int auxR = particioner(vector, getValue, R, L);
	merger(vector, getValue, auxR, L);
	merger(vector, getValue, R, auxR + 1);
}

void strMerger(void **vector, int R, int L, int *aux)
{
	if (R <= L)
		return;

	int auxR = strParticioner(vector, R, L, aux);
	strMerger(vector, auxR, L, aux);
	strMerger(vector, R, auxR + 1, aux);
}

void **quickSort(dicionario dic, int (*getScore)(void *), int (*getBan)(void *), int (*getCertified)(void *), char *(*getName)(void *))
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
				++banned;

			else
				vector[i] = segTuplo(t);

			auxNo = nextNode(auxNo);
			++i;
		}
	}

	numElems = dic->numElems - banned;
	int aux[numElems];
	for (i = 0; i < numElems; ++i)
		aux[i] = strSum(getName(vector[i]));
	strMerger(vector, numElems - 1, 0, aux);
	merger(vector, getCertified, numElems - 1, 0);
	merger(vector, getScore, numElems - 1, 0);
	return vector;
}
