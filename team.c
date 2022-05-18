#include <stdlib.h>
#include <string.h>

#include "team.h"
#include "linkedList.h"
#include "node.h"
#include "archaeologist.h"
#include "iterator.h"

struct _team {
    char* name;
    int score, isBanned;
    node current;
    arc star;
    linkedList archaeologists;
};

team new_team(char* name) {
    team t = malloc(sizeof(struct team));
    if (t == NULL) return NULL;

    t->name = (char*) malloc(sizeof(char)*strlen(name));
    if (t->name == NULL) { free(t); return NULL; }
    strncpy(t->name, name, 40);

    t->archaeologists = newList(0);
    if (t->archaeologists == NULL) { free(t->name); free(t); return NULL; }

    t->isBanned = 0;
    t->score = 0;
    t->star = NULL;
    t->current = NULL;

    return t;
}

void destroy_team(team t) {
    free(t->name);
    if (t->star != NULL) destroyArc(t->star);
    if (t->current != NULL) destroyNode(t->current);
    destroyList(t->archaeologists);
    free(t);
}

void destroy_team_and_elems(team t) {
    free(t->name);
    if (t->star != NULL) destroyArc(t->star);
    if (t->current != NULL) destroyNode(t->current);
    destroyListAndElems(t->archaeologists, destroyArcGen);
    free(t);
}

void destroy_team_gen(void* t) {
    destroy_team((team) t);
}

void destroy_team_and_elems_gen(void* t) {
    destroy_team_and_elems((team) t);
}

void add_arc(team t, char* arcName) {
    arc a = newArchaeologist(arcName);
    insert(t->archaeologists, a, sizeCertified(t->archaeologists));
}

char* team_name(team t)
{
    return t->name;
}

char* team_name_gen(void* t) {
    return team_name((team) t);
}

int get_is_banned(team t) {
    return t->isBanned;
}

int get_is_banned_gen(void* t) {
    return get_is_banned((team) t);
}

arc get_star(team t) {
    return t->star;
}

arc get_act(team t) {
    return (arc) checkElem(t->current);
}

void update_star(team t) {
    t->star = (arc) checkElem(t->current);
}

void next_archaeologist(team t, int pointsMade)
{
    addScore(t->current, pointsMade);
    t->score += pointsMade;

    if (!getCertificate((arc) checkElem(nextNode(t->current)))) {
        t->current = getHead(t->archaeologists);
        return;
    }

    t->current = nextNode(t->current);
}

void ban_elem(team t) {
    node n = nextNode(t->current);

    if (n == NULL)
        n = getHead(t->archaeologists);
    else if (!getCertificate((arc) checkElem(n)))
        n = getHead(t->archaeologists);

    t->score -= getScore(t->current);
    disqualify((arc) getElem(t->current));
        
    moveToTail(t->current);
    t->current = n;

    if (sizeCertified(t->archaeologists) == 0) {
        t->isBanned = 1;
    }

    if (!strcmp(arcName((arc) checkElem(n), arcName(t->star)))) {
        iterator it = listIterator(t->archaeologists);
        if (it == NULL && !has_next_item(it)) return;
        arc a;
        t->sar = next_item(it);

        while(has_next_item(it)) {
            a = next_item(it);
            if (getScore(t->star) < getScore(a))
                t->star = a;
        }
    }
}

int get_team_score(team t) {
    return t->score;
}

int get_team_score_gen(void* t) {
    return get_team_score((team) t);
}

arc exist_arc(team t, char* name) {
    arc a = (arc) getElem(existElem(t->archaeologists, name, getNameGen));
    return a;
}

void set_ban_team(team t) {
    t->isBanned = 1;
}

int total_number(team t) {
    return sizeList(t->archaeologists);
}

int arc_number(team t) {
    return sizeCertified(t->archaeologists);
}

iterator team_iterator(team t) {
    return listIterator(t->archaeologists);
}

