#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "archaeologist.h"
#include "node.h"
#include "iterator.h"
#include "linkedList.h"
#include "team.h"
#include "contest.h"

contest make_initial_contest(team t[]);
void interpreter(contest c, team t[]);
void finish(contest c);
void teamCmd(contest c, team t[], char *buffer);
void reforces(contest c);
void escavation(contest c, char *buffer);
void team_star(contest c, char *buffer);
void Terrain(contest c);
void buriedRichness(contest c);
void destroy_teams(team t[]);
void convert_file_to_array(team t[]);

linkedList newList();

int main()
{
    team t[2000];
    convert_file_to_array(t);
    contest c = make_initial_contest(t);
    interpreter(c, t);
    destroy_contest(c);
    destroy_teams(t);
    return 1;
}

void destroy_teams(team t[])
{
    for (int i = 0; t[i] != NULL && i < 2000; ++i)
        destroy_team_and_elems(t[i]);
}

contest read_terrain()
{
    char ch, buffer[20];
    fgets(buffer, sizeof(buffer), stdin);
    int C, L, aux = 0;

    sscanf(buffer, "%d %d", &L, &C);
    contest c = new_contest(L, C);
    for (int i = 0; i < L; ++i)
    {
        for (int j = 0; j < C;)
        {
            ch = fgetc(stdin);
            if (ch == ' ' || ch == '\n' || ch == EOF)
            {
                set_tile_treasure(c, i, j, aux);
                ++j;
                aux = 0;
            }
            else
                aux = aux * 10 + (ch - '0');
        }
    }
    return c;
}

void convert_file_to_array(team t[])
{
    FILE *fp = fopen("teams.txt", "r");

    char buffer[50];
    int aux = 0;
    team temp;

    for (int i = 0; i < 2000; ++i) {
        t[i] = NULL;
    }

    for (int i = 0; fgets(buffer, sizeof(buffer), fp); ++i)
    {
        sscanf(buffer, "%d", &aux);

        fgets(buffer, sizeof(buffer), fp);
        buffer[strlen(buffer)-1] = '\0';
        temp = new_team(buffer);

        for (int j = 0; j < aux; ++j) {
            fgets(buffer, sizeof(buffer), fp);
            buffer[strlen(buffer)-1] = '\0';
            add_arc(temp, buffer);
        }
        t[i] = temp;
    }
}

int read_console_number()
{
    char ch;
    int aux = 0;
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF)
    {
        aux = aux * 10 + (ch - '0');
    }
    return aux;
}

contest make_initial_contest(team t[])
{
    contest c = read_terrain();

    int f = read_console_number(), aux = 0;
    char ch;

    for (int i = 0; i < f;)
    {
        ch = fgetc(stdin);
        if (ch == ' ' || ch == '\n' || ch == EOF)
        {
            add_team(c, t[aux-1]);
            ++i;
            aux = 0;
        }
        else
            aux = aux * 10 + (ch - '0');
    }

    return c;
}

void interpreter(contest c, team t[])
{
    char cmd[12], buffer[200];
    int i;
    while (1)
    {
        fgets(buffer, sizeof(buffer), stdin);
        for (i = 0; buffer[i] != ' ' && buffer[i] != '\n'; ++i)
            cmd[i] = buffer[i];
        cmd[i] = '\0';

        if (!strcmp(cmd, "riqueza"))
            buriedRichness(c);

        else if (!strcmp(cmd, "terreno"))
            Terrain(c);

        else if (!strcmp(cmd, "estrela"))
            team_star(c, buffer);

        else if (!strcmp(cmd, "escavacao"))
            escavation(c, buffer);

        else if (!strcmp(cmd, "reforco"))
            reforces(c);

        else if (!strcmp(cmd, "equipa"))
            teamCmd(c, t, buffer);

        else if (!strcmp(cmd, "sair"))
        {
            finish(c);
            break;
        }

        else
            printf("Comando invalido\n");
    }
}

void buriedRichness(contest c)
{
    printf("Riqueza enterrada: %d\n", get_burried_treasure(c));
}

void Terrain(contest c)
{
    for (int i = 0; i < get_lines(c); ++i)
    {
        for (int j = 0; j < get_columns(c); ++j)
        {
            if (see_treasure(c, i, j) > 0)
                printf("*");
            else
                printf("-");
        }
        printf("\n");
    }
}

void team_star(contest c, char *buffer)
{

    char name[40];
    sscanf(buffer, "estrela %40[^\n]", name);

    team t = has_team(c, name);
    if (t == NULL)
    {
        printf("Equipa invalida\n");
        return;
    }
    else if(get_ban_team(t)){
        printf("Equipa invalida\n");
        return;
    }
    
    printf("Estrela de %s: %s\n", team_name(t), getName(get_star(t)));
}

void escavation(contest c, char *buffer)
{
    char teamName[40];
    int jumpC, jumpL, *newPos;
    sscanf(buffer, "escavacao %d %d %40[^\n]", &jumpC, &jumpL, teamName);
    if (!jumpC && !jumpL)
    {
        printf("Salto invalido\n");
        return;
    }

    team t = has_team(c, teamName);
    if (t == NULL) {
        printf("Equipa invalida\n");;
        return;
    }
    else if(get_ban_team(t)){
        printf("Equipa invalida\n");
        return;
    }
    arc archeologist = get_act(t);
    if (archeologist == NULL)
        return;

    getNewPos(archeologist, jumpC, jumpL);
    newPos = getPos(archeologist);

    if ((newPos[0] > get_lines(c) - 1 || newPos[0] < 0) || (newPos[1] > get_columns(c) - 1 || newPos[1] < 0))
    {
        ban_elem(t);
        if (get_ban_team(t)) {
            ban_team(c);
            printf("%s foi expulsa\n", teamName);
        }
        return;
    }

    int aux = get_treasure(c, newPos[0], newPos[1]);

    if (aux > 0)
        next_archaeologist(t, aux);
    else
        next_archaeologist(t, aux * 10);
}

void reforces(contest c)
{
    char teamName[40], arcName[40];
    fgets(teamName, sizeof(teamName), stdin);
    fgets(arcName, sizeof(arcName), stdin);

    team t = has_team(c, teamName);
    if (t == NULL)
    {
        printf("Equipa invalida\n");
        return;
    }

    arc a = exist_arc(t, arcName);
    if (a == NULL)
    {
        printf("Arqueologo invalido\n");
        return;
    }

    add_arc(t, arcName);
}

void teamCmd(contest c, team t[], char *buffer)
{
    int nTeam;
    sscanf(buffer, "equipa %d", &nTeam);
    --nTeam;
    if (t[nTeam] == NULL)
    {
        printf("Equipa inexistente\n");
        return;
    }
    else if (has_team(c, team_name(t[nTeam])) != NULL)
    {
        printf("Equipa invalida\n");
        return;
    }

    add_team(c, t[nTeam]);
}

void finish(contest c)
{
    if (!get_certified_teams(c))
    {
        printf("Todas as equipas foram expulsas.\n");
        return;
    }
    if (get_burried_treasure(c))
    {
        printf("Ainda havia tesouros por descobrir...\n");
        return;
    }

    printf("Todos os tesouros foram descobertos!\n");
    return;
}
