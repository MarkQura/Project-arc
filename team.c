#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "iterator.h"
#include "linkedList.h"
#include "archaeologist.h"
#include "team.h"

#define NAME_SIZE 50

//This ADT will be used to hold, give and change the information of a team 
struct _team
{
    char name[NAME_SIZE];
    int score, isBanned;
    node current;
    arc star;
    dicionario archaeologists;
};

team new_team(char *name)
{
    team t = malloc(sizeof(struct _team));
    if (t == NULL)
        return NULL;

    t->archaeologists = newList();
    if (t->archaeologists == NULL)
    {
        free(t->name);
        free(t);
        return NULL;
    }

    strncpy(t->name, name, 40);
    t->isBanned = 0;
    t->score = 0;
    t->star = NULL;
    t->current = NULL;

    return t;
}

void destroy_team(team t)
{
    destroyList(t->archaeologists);
    free(t);
}

void destroy_team_and_elems(team t)
{
    destroyListAndElems(t->archaeologists, destroyArcGen);
    free(t);
}

void destroy_team_gen(void *t) { destroy_team((team)t); }

void destroy_team_and_elems_gen(void *t) { destroy_team_and_elems((team)t); }

void add_arc(team t, char *arcName)
{
    arc a = newArc(arcName);
    insert(t->archaeologists, a, sizeCertified(t->archaeologists));

    if (t->current == NULL)
    {
        t->current = getHead(t->archaeologists);
        t->star = a;
        return;
    }

    if (getScore(t->star) == 0)
    {
        int comp = strcmp(getName(t->star), arcName);
        if (comp > 0)
            t->star = a;
        return;
    }
}

char *team_name(team t) { return t->name; }

char *team_name_gen(void *t) { return team_name((team)t); }

arc get_star(team t) { return t->star; }

arc get_act(team t) { return (arc)getElem(t->current); }

void find_team_star(team t)
{
    iterator it = certifiedIterator(t->archaeologists);
    if (it == NULL && !has_next_item(it))
        return;
    arc a;
    int comp, penalty;
    t->star = next_item(it);

    while (has_next_item(it))
    {
        a = next_item(it);
        comp = getScore(t->star) - getScore(a);

        if (comp < 0)
            t->star = a;

        else if (comp == 0)
        {
            penalty = getPenalty(t->star) - getPenalty(a);

            if (penalty > 0)
                t->star = a;

            else if (penalty == 0)
                if (strcmp(getName(t->star), getName(a)) > 0)
                    t->star = a;
        }
    }
}

void next_archaeologist(team t, int pointsMade)
{
    arc a = (arc)getElem(t->current);
    addScore(a, pointsMade);
    t->score += pointsMade;
    int comp = getScore(t->star) - getScore(a), penalty;

    if (pointsMade < 0)
    {
        addPenalty(a);
        if (t->star == a) {
            find_team_star(t);
            goto skip;
        }
    }

    else if (comp < 0)
        t->star = a;

    else if (comp == 0)
    {
        penalty = getPenalty(t->star) - getPenalty(a);

        if (penalty > 0)
            t->star = a;

        else if (penalty == 0)
            if (strcmp(getName(t->star), getName(a)) > 0)
                t->star = a;
    }

    skip:;
    node temp = nextNode(t->current);
    if (temp == NULL)
    {
        t->current = getHead(t->archaeologists);
        return;
    }

    if (!getCertificate((arc)getElem(temp)))
    {
        t->current = getHead(t->archaeologists);
        return;
    }

    t->current = temp;
}

void ban_elem(team t)
{
    node n = nextNode(t->current);

    if (n == NULL)
        n = getHead(t->archaeologists);
    else if (!getCertificate((arc)getElem(n)))
    {
        n = getHead(t->archaeologists);
        goto skip;
    }

    moveToTail(t->archaeologists, t->current);

skip:;
    arc a = (arc)getElem(t->current);
    t->score -= getScore(a);
    desqualify(a);
    decrementCertified(t->archaeologists);

    if (sizeCertified(t->archaeologists) == 0)
    {
        t->isBanned = 1;
        return;
    }

    if (!strcmp(getName(a), getName(t->star)))
        find_team_star(t);

    t->current = n;
}

arc exist_arc(team t, char *name)
{
    arc a = (arc)getElem(existElem(t->archaeologists, name, getNameGen));
    return a;
}

int get_ban_team(team t) { return t->isBanned; }

iterator team_iterator(team t) { return listIterator(t->archaeologists); }

/* int arc_number(team t) { return sizeCertified(t->archaeologists); }

int get_team_score(team t) { return t->score; }

int get_team_score_gen(void *t) { return get_team_score((team)t); }

int get_is_banned_gen(void *t) { return get_ban_team((team)t); }
*/
