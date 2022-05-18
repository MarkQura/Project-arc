#include <stdlib.h>

#include "node.h"
#include "team.h"
#include "tile.h"
#include "linkedList.h"
#include "iterator.h"
#include "contest.h"

struct _contest {
    tile terrain[30][30];
    int burriedTreasure, lines, columns;
    linkedList teams;
    node currentTeam;
};

contest new_contest(int lines, int columns) {
    contest c = (contest) malloc(sizeof(struct _contest));
    if (c == NULL) return NULL;

    c->teams = newList();
    if (c->teams == NULL) { free(c); return NULL; }
    
    c->lines = lines;
    c->columns = columns;
    c->burriedTreasure = 0;
    return c;
}

void destroy_contest(contest c) {
    destroyList(c->teams);
    free(c);
}

void destroy_contest_elem(contest c) {
    for (int i = 0; i < c->line; ++i) {
        for (int j = 0; j < c->columns; ++j) {
            destroy_tile(c[i][j]);
        }
    }

    destroyListAndElems(c->teams, destroy_team_and_elems_gen);
    free(c);
}

void add_team(contest c, team t) {
    insert(c->teams, t, sizeCertified(c->teams));
}

team has_team(contest c, char* name) {
    c->currentTeam = existElem(c->teams, name, team_name_gen);
    return (team) getElem(c->currentTeam);
}

void set_tile_treasure(contest c, int line, int column, int treasure) {
    tile t = new_tile(treasure);
    c->terrain[line][column] = t;
    c->burriedTreasure += treasure;
}

int get_lines(contest c) {
    return c->lines;
}

int get_columns(contest c) {
    return c->columns;
}

tile get_tile(contest c, int line, int column) {
    return c->terrain[line][column];
}

void sort_teams(contest c) {
    sortList(c->teams, get_team_score_gen, destroy_team_and_elems_gen);
}

void ban_team(contest c) {
    set_ban_team((team) getElem(c->currentTeam));
    moveToTail(c->currentTeam);
}

iterator contest_iterator (contest c) {
    return listIterator(c->teams);
}