#ifndef CONTEST_H
#define CONTEST_H

typedef struct _contest * contest;

/***********************************************
criaContest - Criacao da instancia da estrutura associada a um concurso.
Parametros:
	lines - numeros de linhas
    columns - numeros de colunas
Retorno: apontador para a instancia criada
Pre-condicoes: lines != 0 e columns != 0
***********************************************/
contest new_contest(int lines, int columns);

/***********************************************
destroiConcurso - Liberta a memoria ocupada pela instancia da estrutura associada ao concurso.
Parametros:
	c - concurso a destruir
Retorno:
Pre-condicoes: c != NULL
***********************************************/
void destroy_contest(contest c);

/***********************************************
destroiConcursoElems - Liberta a memoria ocupada pela instancia da estrutura associada ao concurso e os seus elementos.
Parametros:
	c - concurso a destruir
Retorno:
Pre-condicoes: c != NULL
***********************************************/
void destroy_contest_elem(contest c);

/***********************************************
existeEquipa - ve se o archeologo de nome.
Parametros:
	c - concurso
	name - nome da equipa a encontrar
Retorno: equipa se encontrou, NULL se não
Pre-condicoes: c != NULL
***********************************************/
team has_team(contest c, char* name);

/***********************************************
adicionaEquipa - adiciona uma equipa ao concurso.
Parametros:
	c - concurso
	name - nome da equipa a adicionar
Retorno: 
Pre-condicoes: c != NULL
***********************************************/
void add_team(contest c, char *name);

/***********************************************
existeArc - ve se o archeologo de nome.
Parametros:
	c - concurso
	name - nome da equipa a encontrar
Retorno: equipa se encontrou, NULL se não
Pre-condicoes: c != NULL
***********************************************/
void set_tile_treasure(contest c, int line, int column, int treasure);

/***********************************************
linhas - ve o numero de linhas do terreno.
Parametros:
	c - concurso
Retorno: numero de linhas do terreno
Pre-condicoes: c != NULL
***********************************************/
int get_lines(contest c);~

/***********************************************
colunas - ve o numero de colunas do terreno.
Parametros:
	c - concurso
Retorno: numero de colunas do terreno
Pre-condicoes: c != NULL
***********************************************/
int get_columns(contest c);

/***********************************************
talha - ve a talha na posição.
Parametros:
	c - concurso
    line - linha
    column - coluna
Retorno: equipa se encontrou, NULL se não
Pre-condicoes: c != NULL &&  0 <= line <= L && 0 <= column <= C
***********************************************/
tile get_tile(contest c, int line, int column);

/***********************************************
ordenaEquipas - ordena as equipas em ordem decrescente.
Parametros:
	c - concurso
    line - linha
    column - coluna
Retorno:
Pre-condicoes: c != NULL
***********************************************/
void sort_teams(contest c);

/***********************************************
iteraEquipa - cria um iterador da equipa.
Parametros:
	t - equipa
Retorno: iterador da equipa
Pre-condicoes:  t != NULL
***********************************************/
iterator contest_iterator (contest c);

#endif