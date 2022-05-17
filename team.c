#include <stdlib.h>
#include <string.h>
#include "team.h"
#include "linkedList.h"
#include "node.h"
#include "archaeologist.h"
#include "iterator.h"

struct _team {
    char* name;
    int merit;
    node current;
    arc star;
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

char* team_name_gen(void* t) {
    return team_name((team) t);
}

arc get_star(team t)
{
    return t->star;
}

arct get_act(team t)
{
    return (arc) checkElem(t->current);
}

void update_star(team t) {
    t->star = (arc) checkElem(t->current);
}

void next_archaeologist(team t)
{
    if (!getCertificate((arc) checkElem(nextNode(t->current)))) {
        t->current = getHead(t->archaeologists);
        return;
    }
    t->current = nextNode(t->current);
}

void ban_elem(team t)
{
    node n = nextNode(t->current);

    if (n == NULL)
        n = getHead(t->archaeologists);
    else if (!getCertificate((arc) checkElem(n)))
        n = getHead(t->archaeologists);
        
    moveToTail(t->current);
    t->current = n;

    if (!strcmp(arcName((arc) checkElem(n), arcName(t->star)))) {
        iterator it = listIterator(t->archaeologists);
        if (it == NULL && has_next_item(it)) return;
        archaeologist a;
        t->sar = next_item(it);

        while(has_next_item(it)) {
            a = next_item(it);
            if (getMerit(t->star) < getMerit(a))
                t->star = a;
        }
    }
}

int exist_arc(team t, char* name) {
    return existElem(t->archaeologists, name, getNameGen);
}

int arc_number(team t) {
    return sizeCertified(t->archaeologists);
}

iterator team_iterator(team t)
{
    return listIterator(t->archaeologists);
}

