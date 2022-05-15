#ifndef TEAM_H
#define TEAM_H

typedef struct _team * team;

team new_team(char* name);

void add_elem(team t, char* arcName);

char* team_name(team t);

void* get_star(team t);

iterator team_iterator(team t);

#endif