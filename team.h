#ifndef TEAM_H
#define TEAM_H

typedef struct _team * team;

/***********************************************
criaEquipa - Criacao da instancia da estrutura associada a uma equipa.
Parametros:
	nome - nome associado a uma equipa
Retorno: apontador para a instancia criada
Pre-condicoes:
***********************************************/
team new_team(char* name);

/***********************************************
destroiEquipa - Liberta a memoria ocupada pela instancia da estrutura associada a equipa.
Parametros:
	t - equipa a destruir
Retorno:
Pre-condicoes: t != NULL
***********************************************/
void destroy_team(team t);

/***********************************************
destroiEquipaElems - Liberta a memoria ocupada pela instancia da estrutura associada a equipa e os seus elementos.
Parametros:
	t - equipa a destruir
Retorno:
Pre-condicoes: t != NULL
***********************************************/
void destroy_team_and_elems(team t);

/***********************************************
destroiEquipaGen - Liberta a memoria ocupada pela instancia da estrutura associada a equipa.
Parametros:
	t - equipa a destruir
Retorno:
Pre-condicoes: t != NULL
***********************************************/
void destroy_team_gen(void* t);

/***********************************************
destroiEquipaElemsGen - Liberta a memoria ocupada pela instancia da estrutura associada a equipa e os seus elementos.
Parametros:
	t - equipa a destruir
Retorno:
Pre-condicoes: t != NULL
***********************************************/
void destroy_team_and_elems_gen(void* t);

/***********************************************
addArc - adiciona um arqueologo à equipa.
Parametros:
	t - equipa
    arcName - nome do arqueologo
Retorno:
Pre-condicoes:  t != NULL
***********************************************/
void add_arc(team t, char* arcName);

/***********************************************
equipaNome - vai buscar o nome da equipa.
Parametros:
	t - equipa
Retorno: devolve nome da equipa
Pre-condicoes:  t != NULL
***********************************************/
char* team_name(team t);

/***********************************************
equipaNomeGen - vai buscar o nome da equipa.
Parametros:
	t - equipa
Retorno: devolve nome da equipa
Pre-condicoes:  t != NULL
***********************************************/
char* team_name_gen(void* t);

/***********************************************
melhorArc - vai buscar o arqueologo com mais pontos da equipa.
Parametros:
	t - equipa
Retorno: devolve o elemento da equipa com mais pontos
Pre-condicoes:  t != NULL
***********************************************/
arc get_star(team t);

/***********************************************
buscaAtual - vai buscar o arqueologo a escavar a seguir.
Parametros:
	t - equipa
Retorno: o proximo elemento da equipa a escavar
Pre-condicoes:  t != NULL
***********************************************/
arc get_act(team t);

/***********************************************
atualizaEstrela - vai atualizar a estrela da equipa.
Parametros:
	t - equipa
Retorno:
Pre-condicoes:  t != NULL && getMerit(current) > getMerit(star)
***********************************************/
void update_star(team t);

/***********************************************
proximoArc - passa o arqueologo atual para o proximo.
Parametros:
	t - equipa
Retorno:
Pre-condicoes:  t != NULL && getCertificate((archeologist) checkElem(t->current)) == 1
***********************************************/
void next_archaeologist(team t);

/***********************************************
baneElem - bane o elemento atual da equipa e passa para o proximo.
Parametros:
	t - equipa
Retorno:
Pre-condicoes:  t != NULL && getCertificate((archeologist) checkElem(t->current)) == 1
***********************************************/
void ban_elem(team t);

/***********************************************
iteraEquipa - cria um iterador da equipa.
Parametros:
	t - equipa
Retorno: iterador da equipa
Pre-condicoes:  t != NULL
***********************************************/
iterator team_iterator(team t);

/***********************************************
numeroArc - ve o numero de arqueologos certificados na equipa.
Parametros:
	t - equipa
Retorno: numero de arqueologos certificados
Pre-condicoes:  t != NULL
***********************************************/
int arc_number(team t);

/***********************************************
numeroTotal - ve o numero total de arqueologos na equipa.
Parametros:
	t - equipa
Retorno: numero de arqueologos certificados
Pre-condicoes:  t != NULL
***********************************************/
int total_number(team t);

/***********************************************
existeArc - ve se o archeologo de nome.
Parametros:
	t - equipa
	name - nome do arqueologo a encontrar
Retorno: arqueologo se encontrou, NULL se não
Pre-condicoes:  t != NULL
***********************************************/
arc exist_arc(team t, char* name);

/***********************************************
pontuaçãoEquipa - ve a pontuação da equipa.
Parametros:
	t - equipa
Retorno: pontuação da equipa
Pre-condicoes:  t != NULL
***********************************************/
int get_team_score(team t);

/***********************************************
pontuaçãoEquipa - ve a pontuação da equipa.
Parametros:
	t - equipa
Retorno: pontuação da equipa
Pre-condicoes:  t != NULL
***********************************************/
int get_team_score_gen(void* t);

/***********************************************
baneEquipa - bane a equipa.
Parametros:
	t - equipa
Retorno:
Pre-condicoes:  t != NULL
***********************************************/
void set_ban_team(team t);

#endif