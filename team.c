#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "iterador.h"
#include "dicionario.h"
#include "archaeologist.h"
#include "team.h"

#define NAME_SIZE 50
#define TEAM_SIZE 500

// This ADT will be used to hold, give and change the information of a team
struct _team
{
    char name[NAME_SIZE];
    char arcs[TEAM_SIZE][NAME_SIZE];
    int score, isBanned, current, size, bannedArcs;
    arc star;
    dicionario archaeologists;
};

team new_team(char *name)
{
    team t = malloc(sizeof(struct _team));
    if (t == NULL)
        return NULL;

    t->archaeologists = criaDicionario(TEAM_SIZE, 1);
    if (t->archaeologists == NULL)
    {
        free(t);
        return NULL;
    }

    strncpy(t->name, name, 40);
    t->isBanned = 0;
    t->score = 0;
    t->star = NULL;
    t->current = 0;
    t->size = 0;
    t->bannedArcs = 0;

    return t;
}

void destroy_team(team t)
{
    destroiDicionario(t->archaeologists);
    free(t);
}

void destroy_team_and_elems(team t)
{
    destroiDicEElems(t->archaeologists, destroyArcGen);
    free(t);
}

void destroy_team_gen(void *t) { destroy_team((team)t); }

void destroy_team_and_elems_gen(void *t) { destroy_team_and_elems((team)t); }

void add_arc(team t, char *arcName)
{
    arc a = newArc(arcName);
    adicionaElemDicionario(t->archaeologists, a, arcName);
    strncpy(t->arcs[t->size], arcName, NAME_SIZE);

    if (t->size == 0)
    {
        t->star = a;
        goto incSize;
    }

    else if (getScore(t->star) == 0)
    {
        if (getPenalty(t->star) != 0)
            t->star = a;
        goto incSize;

        int comp = strcmp(getName(t->star), arcName);
        if (comp > 0)
            t->star = a;
    }

    else if (getScore(t->star) < 0)
        t->star = a;

incSize:
    ++t->size;
}

char *team_name(team t) { return t->name; }

char *team_name_gen(void *t) { return team_name((team)t); }

arc get_star(team t) { return t->star; }

arc get_act(team t) { return (arc)elementoDicionario(t->archaeologists, t->arcs[t->current]); }

void find_team_star(team t)
{
    arc a;
    int comp, penalty;
    t->star = (arc)elementoDicionario(t->archaeologists, t->arcs[0]);

    for (int i = 1; i < t->size; ++i)
    {
        a = (arc)elementoDicionario(t->archaeologists, t->arcs[i]);
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
    arc a = (arc)elementoDicionario(t->archaeologists, t->arcs[t->current]);
    addScore(a, pointsMade);
    t->score += pointsMade;
    int comp = getScore(t->star) - getScore(a), penalty;

    if (pointsMade < 0)
    {
        addPenalty(a);
        if (t->star == a)
        {
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
    if (t->current == t->size)
    {
        t->current = 0;
        return;
    }

    ++t->current;
}

void ban_elem(team t)
{

    arc a = removeElemDicionario(t->archaeologists, t->arcs[t->current]);
    t->score -= getScore(a);
    desqualify(a);
    strcpy(t->arcs[t->size], t->arcs[t->current]);
    for (int i = t->current; i < t->size; ++i)
    {
        strcpy(t->arcs[i], t->arcs[i + 1]);
    }
    --t->size;

    if (t->size == 0)
    {
        t->isBanned = 1;
        goto incCur;
    }

    if (!strcmp(getName(a), getName(t->star)))
        find_team_star(t);

incCur:;

    if (t->current == t->size)
    {
        t->current = 0;
        return;
    }

    ++t->current;
    ++t->bannedArcs;
}

arc exist_arc(team t, char *name) { return (arc)elementoDicionario(t->archaeologists, name); }

int get_ban_team(team t) { return t->isBanned; }

int get_ban_arcs_team(team t) { return t->bannedArcs; }

int get_certified_arcs(team t) { return tamanhoDicionario(t->archaeologists) - t->bannedArcs; }

iterador team_iterator(team t) { return iteradorDicionario(t->archaeologists); }

iterador team_names_iterator(team t) { return iteradorChaveDicionario(t->archaeologists); }

int get_team_score(team t) { return t->score; }

int get_team_score_gen(void *t) { return get_team_score((team)t); }

/* int arc_number(team t) { return sizeCertified(t->archaeologists); }

int get_is_banned_gen(void *t) { return get_ban_team((team)t); }
*/
