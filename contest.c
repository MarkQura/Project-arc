#include <stdlib.h>

#include "node.h"
#include "iterador.h"
#include "archaeologist.h"
#include "dicionario.h"
#include "team.h"
#include "priorityQueue.h"
#include "contest.h"

#define MAX_ROWS_COLS 30
#define MAX_EQUIPAS 1000
#define MAX_ARCS 500000

// This ADT will be used to hold, give and change the information of the contest itself
struct _contest
{
    int terrain[MAX_ROWS_COLS][MAX_ROWS_COLS];
    int burriedTreasure, lines, columns, sizeCertified;
    dicionario teams;
};

contest new_contest(int lines, int columns)
{
    contest c = (contest)malloc(sizeof(struct _contest));
    if (c == NULL)
        return NULL;

    c->teams = criaDicionario(MAX_EQUIPAS, 1);
    if (c->teams == NULL)
    {
        free(c);
        return NULL;
    }

    c->lines = lines;
    c->columns = columns;
    c->burriedTreasure = 0;
    c->sizeCertified = 0;
    return c;
}

void destroy_contest(contest c)
{
    destroiDicionario(c->teams);
    free(c);
}

void destroy_contest_elem(contest c)
{
    destroiDicEElems(c->teams, destroy_team_and_elems_gen);
    free(c);
}

void add_team(contest c, team t)
{
    adicionaElemDicionario(c->teams, team_name(t), t);
    ++c->sizeCertified;
}

team has_team(contest c, char *name)
{
    team t = (team)elementoDicionario(c->teams, name);
    return t;
}

void set_tile_treasure(contest c, int line, int column, int treasure)
{
    c->terrain[line][column] = treasure;
    c->burriedTreasure += treasure;
}

int see_treasure(contest c, int line, int column) { return c->terrain[line][column]; }

int get_treasure(contest c, int line, int column)
{
    int treasure = c->terrain[line][column];
    if (c->terrain[line][column] > 0)
    {
        c->burriedTreasure -= treasure;
        c->terrain[line][column] = -1;
    }
    else
        c->terrain[line][column] -= 1;

    return treasure;
}

int get_burried_treasure(contest c) { return c->burriedTreasure; }

int get_lines(contest c) { return c->lines; }

int get_columns(contest c) { return c->columns; }

void ban_team(contest c) { --c->sizeCertified; }

int get_certified_teams(contest c) { return c->sizeCertified; }

pQueue sort_teams(contest c) { 
    int numElems = 0;
    team * temp = (team *)quickSort(c->teams, &numElems, get_ban_team_gen);
    pQueue pq = newPQueue(numElems);
    
    for (int i = 0; i < numElems; ++i)
        adicionaElemPq(pq, temp[i]);
    
    free(temp);
    return pq;
}

iterador contest_teams_iterator(contest c) { return iteradorDicionario(c->teams); }

iterador contest_team_names_iterator(contest c) { return iteradorChaveDicionario(c->teams); }