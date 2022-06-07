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
    int score, isBanned, current, bannedArcs;
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
    t->bannedArcs = 0;
    t->star = NULL;
    t->current = 0;

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
    adicionaElemDicionario(t->archaeologists, getName(a), a);
    strncpy(t->arcs[tamanhoDicionario(t->archaeologists) - 1], getName(a), NAME_SIZE);

    if (tamanhoDicionario(t->archaeologists) == 1)
    {
        t->star = a;
    }

    else if (getScore(t->star) == 0)
    {
        if (getPenalty(t->star) != 0)
        {
            t->star = a;
        }

        int comp = strcmp(getName(t->star), getName(a));
        if (comp > 0)
            t->star = a;
    }

    else if (getScore(t->star) < 0)
        t->star = a;
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

    for (int i = 1; i < tamanhoDicionario(t->archaeologists) - t->bannedArcs; ++i)
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
    ++t->current;

    if (t->current == tamanhoDicionario(t->archaeologists) - t->bannedArcs)
        t->current = 0;
}

void ban_elem(team t)
{
    arc a = elementoDicionario(t->archaeologists, t->arcs[t->current]);
    ++t->bannedArcs;
    t->score -= getScore(a);
    desqualify(a);

    for (int i = t->current; i < tamanhoDicionario(t->archaeologists) - t->bannedArcs; ++i)
        strcpy(t->arcs[i], t->arcs[i + 1]);

    if (tamanhoDicionario(t->archaeologists) - t->bannedArcs == 0)
    {
        t->isBanned = 1;
    }

    else if (!strcmp(getName(a), getName(t->star)))
        find_team_star(t);

    if (t->current == tamanhoDicionario(t->archaeologists) - t->bannedArcs)
        t->current = 0;
}

arc exist_arc(team t, char *name) { return (arc)elementoDicionario(t->archaeologists, name); }

int get_ban_team(team t) { return t->isBanned; }

int get_ban_arcs_team(team t) { return t->bannedArcs; }

int get_team_score(team t) { return t->score; }

int get_team_score_gen(void *t) { return get_team_score((team)t); }

int get_certified_arcs(team t) { return tamanhoDicionario(t->archaeologists) - t->bannedArcs; }

iterador team_iterator(team t) { return iteradorDicionario(t->archaeologists); }

iterador team_names_iterator(team t) { return iteradorChaveDicionario(t->archaeologists); }

/* int arc_number(team t) { return sizeCertified(t->archaeologists); }

int get_is_banned_gen(void *t) { return get_ban_team((team)t); }
*/
