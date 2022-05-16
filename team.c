#include <stdlib.h>
#include <string.h>
#include "team.h"
#include "linkedList.h"
#include "archaeologist.h"

struct _team {
    char* name;
    int merit;
    node current; //usar nextElem e verificar se tem certificado se nao voltar para head da lista
    archaeologist star;
    linkedList archaeologists;
};

team new_team(char* name)
{
    team t = malloc(sizeof(struct team));
    if (t == NULL) return NULL;

    t->name = (char*) malloc(sizeof(char)*strlen(name));
    if (t->name == NULL) { free(t); return NULL; }
    strncpy(t->name, name, 40);

    t->archaeologists = newList(0);
    if (t->archaeologists == NULL) { free(t->name); free(t); return NULL; }

    t->merit = 0;
    t->star = NULL;
    t->current = NULL;

    return t;
}

void destroy_team(team t)
{
    free(t->name);
    if (t->star != NULL) destroyArc(t->star);
    if (t->current != NULL) destroyNode(t->current);
    destroyList(t->archaeologists);
    free(t);
}

void destroy_team_and_elems(team t)
{
    free(t->name);
    if (t->star != NULL) destroyArc(t->star);
    if (t->current != NULL) destroyNode(t->current);
    destroyListAndElems(t->archaeologists, destroyArcGen);
    free(t);
}

void destroy_team_gen(void* t)
{
    destroy_team((team) t);
}

void destroy_team_and_elems_gen(void* t)
{
    destroy_team_and_elems((team) t);
}

void add_arc(team t, char* arcName)
{
    archaeologist arc = newArchaeologist(arcName);
    insert(t->archaeologists, arc, sizeCertified(t->archaeologists));
}

char* team_name(team t)
{
    return t->name;
}

void* get_star(team t)
{
    return t->star;
}

archaeologist get_act(team t)
{
    return t->current;
}

void next_archaeologist(team t)
{
    
}

void ban_elem(team t)
{
    
}

iterator team_iterator(team t)
{
    
}

