#ifndef CONTEST_H
#define CONTEST_H

typedef struct _contest *contest;

/***********************************************
new_contest - Criacao da instancia da estrutura associada a um concurso.
Parametros:
	lines - numeros de linhas
	columns - numeros de colunas
Retorno: apontador para a instancia criada
Pre-condicoes: lines != 0 e columns != 0
***********************************************/
contest new_contest(int lines, int columns);

/***********************************************
destroy_contest - Liberta a memoria ocupada pela instancia da estrutura associada ao concurso.
Parametros:
	c - concurso a destruir
Retorno:
Pre-condicoes: c != NULL
***********************************************/
void destroy_contest(contest c);

/***********************************************
destroy_contest_elem - Liberta a memoria ocupada pela instancia da estrutura associada ao concurso e os seus elementos.
Parametros:
	c - concurso a destruir
Retorno:
Pre-condicoes: c != NULL
***********************************************/
void destroy_contest_elem(contest c);

/***********************************************
sort_teams - organiza as equipas por ordem decrescente de pontos, crescente de numero de arquologos e crescente por ordem alfabética
Parametros:
	c - concurso a ordenar
Retorno: matriz de todas as equipas ordenadas
Pre-condicoes: c != NULL
***********************************************/
pQueue sort_teams(contest c);

/***********************************************
has_team - ve se a equipa existe.
Parametros:
	c - concurso
	name - nome da equipa a encontrar
Retorno: equipa se encontrou, NULL se não
Pre-condicoes: c != NULL
***********************************************/
team has_team(contest c, char *name);

/***********************************************
has_arc - ve se o arqueologo está no concurso
Parametros:
	c - concurso
	name - nome da equipa a encontrar
Retorno: equipa se encontrou, NULL se não
Pre-condicoes: c != NULL
***********************************************/
arc has_arc(contest c, char *name);

/***********************************************
add_team - adiciona uma equipa ao concurso.
Parametros:
	c - concurso
	team - equipa a adicionar
Retorno:
Pre-condicoes: c != NULL && team != NULL
***********************************************/
void add_team(contest c, team t);

/***********************************************
set_tile_treasure - dá um valor ao tile na posição indicada.
Parametros:
	c - concurso
	line - linha onde o talhao está na matriz de talhaos
	column - coluna onde o talhao está na matriz de talhaos
	treasure - valor do tesouro a meter no talhao
Retorno: equipa se encontrou, NULL se não
Pre-condicoes: c != NULL && -1 < line < c.line && -1 < column < c.column
***********************************************/
void set_tile_treasure(contest c, int line, int column, int treasure);

/***********************************************
get_lines - ve o numero de linhas do terreno.
Parametros:
	c - concurso
Retorno: numero de linhas do terreno
Pre-condicoes: c != NULL
***********************************************/
int get_lines(contest c);

/***********************************************
get_columns - ve o numero de colunas do terreno.
Parametros:
	c - concurso
Retorno: numero de colunas do terreno
Pre-condicoes: c != NULL
***********************************************/
int get_columns(contest c);

/***********************************************
get_treasure - ve o tesouro na posição.
Parametros:
	c - concurso
	line - linha
	column - coluna
Retorno: tesouro do terreno naquela posição
Pre-condicoes: c != NULL &&  0 <= line <= L && 0 <= column <= C
***********************************************/
int get_treasure(contest c, int line, int column);

/***********************************************
get_burried_treasure - ve o tesouro ainda por desinterrar.
Parametros:
	c - concurso
Retorno: o valor do tesousro enterrado
Pre-condicoes: c != NULL && 0 <= line <= L && 0 <= column <= C
***********************************************/
int get_burried_treasure(contest c);

/***********************************************
get_certified_teams - vê quantas equipas ainda estão no concurso.
Parametros:
	c - concurso
Retorno: numero de equipas ainda no concurso
Pre-condicoes: c != NULL
***********************************************/
int get_certified_teams(contest c);

/***********************************************
ban_team - bane uma equipa.
Parametros:
	c - consurso
Retorno: iterador da equipa
Pre-condicoes:  c != NULL
***********************************************/
void ban_team(contest c);

/***********************************************
see_treasure - ve o valor do talhão escolhido.
Parametros:
	c - consurso
	line - linha onde o talhão está
	column - coluna onde o talhão está
Retorno: iterador da equipa
Pre-condicoes:  c != NULL
***********************************************/
int see_treasure(contest c, int line, int column);

/***********************************************
contest_iterator - cria um iterador da equipa.
Parametros:
	c - concurso
Retorno: iterador da equipa
Pre-condicoes:  c != NULL && 0 <= line <= L && 0 <= column <= C
***********************************************/
iterador contest_teams_iterator(contest c);

#endif