#include <stdio.h>
#include <stdlib.h>

#include "tile.h"
#include "team.h"
#include "contest.h"
#include "iterator.h"
#include "archeologist.h"

contest make_initial_contest();
void interpreter(contest c);

int main() {
    contest c = make_initial_contest();
    interpreter(c);
    destroy_contest(c);
    return 1;
}

contest read_terrain() {
    char ch, buffer[20];
    fgets(buffer, sizeof(buffer), stdin);
    int C, L, aux;

    sscanf(buffer, "%d %d", &L, &C);
    contest c = new_contest(L, C);
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < C;) {
            ch = fgetc(stdin);
            if (ch == ' ' || ch == '\n' || ch == EOF) {
                set_tile_treasure(c, i, j, aux);
                ++j;
                aux = 0;
            }
            else
                aux = aux*10 + (ch - '0');
        }
    }
    return c;
}

team find_team(int f) {

    FILE *fp = fopen("teams.txt", "r");
    
    char ch, buffer[40];
    int aux = 0;

    for (int i = 0; i < f; ++i, aux = 0) {
        while((ch = fgetc(stdin)) != '\n' && (ch = fgetc(stdin)) != EOF) { 
            aux = aux*10 + (ch - '0');
        ++aux;
        }
        for (int j = 0; j < aux; ++j) {
            fgets(buffer, sizeof(buffer), fp);
        }
    }

    while((ch = fgetc(stdin)) != '\n' && (ch = fgetc(stdin)) != EOF) { 
        aux = aux*10 + (ch - '0');
    }

    fgets(buffer, sizeof(buffer), fp);
    team t = new_team(buffer);

    for (int i = 0; i < aux; ++i) {
        fgets(buffer, sizeof(buffer), fp);
        add_arc(t, buffer);
    }

    return t; 
}

int read_console_number() {
    char ch;
    int aux = 0;
    while((ch = fgetc(stdin)) != '\n' && (ch = fgetc(stdin)) != EOF) { 
        aux = aux*10 + (ch - '0');
    }
}

contest make_initial_contest() {
    contest c = read_terrain();

    int f = read_console_number();
    
    for (int i = 0; i < f; ++i) {
        team t = find_team(c, read_console_number());
        add_team(c, t);
    }
    
    return c;
}

void interpreter(contest c){
    char* cmd[12], buffer[20];
    while(1){
        while(buffer[i] != ' '){
            cmd[i] = buffer[i];
            i++;
        }
        if(!strcmp(cmd, "riqueza"))
            buriedRichness(c);
        else if(!strcmp(cmd, "terrain"))
            Terrain(c);
        else if(!strcmp(cmd, "estrela"))
            team_star(c, buffer);
        else if(!strcmp(cmd, "escavacao"))
            escavation(c, buffer);
        else if(!strcmp(cmd, "reforco"))
            reforces(c);
        else if(!strcmp(cmd, "equipa"))
            teamCmd(c)
        else if(!strcmp(cmd, "sair")){
            finish(c);
            break;
        }
        else
            printf("Comando invalido\n");
    }
}

void buriedRichness(contest c){
    printf("%d", getCurrentRichness(c));
}

void Terrain(contest c){
    for(int i = 0; i < get_lines(c); ++i){
        for(int j = 0; j < get_colums(c); ++j){
            if(get_treasure(get_tile(c, i, j)) == 0)
                printf("-")
            else
                printf("*")
        }
        printf("\n");
    }
}

void team_star(contest c, char* buffer) {

    char name[40];
    sscanf(buffer, "estrela %40[^\n]", name);

    team t = has_team(c, name);
    if (t == NULL) { printf("Equipa invalida\n"); return; }

    printf("Star%s: %s", team_name(t), arcName(get_star(t)));
}

void escavation(contest c, char* buffer){
    char teamName[40];
    int jumpC, jumpL, newPos[2];
    sscanf(buffer, "escavacao %d %d %40[^\n]", jumpC, jumpL, teamName);
    if(!jumpC && !jumpL){
        printf("Salto invalido");
        return;
    }
    team t = has_team(jumpC, teamName);
    arc archeologist = get_act(team t);
    newPos = getNewPos(archeologist, jumpC, jumpL);
    if(newPos[0] > get_lines(c) || newPos[0] < 0){
        ban_elem(archeologist);
        return;
    }
    if(newPos[1] > get_colums(c) || newPos[1] < 0){
        ban_elem(archeologist);
        return;
    }
    {tresure, nExcavated} = inc_excavated(get_tile(c, i, j));

    next_archaeologist(team t);
}

void reforces(contest c) {
    char teamName[40], arcName[40];
    fgets(teamName, sizeof(teamName), stdin);
    fgets(arcName, sizeof(arcName), stdin);

    team t = has_team(c, teamName);
    if (t == NULL){ printf("Equipa invalida\n"); return;}

    arc a = exist_arc(t, arcName);
    if (a == NULL) { printf("Arqueologo invalido\n"); return;}

    insert(t, a, arc_number(t));
}

void teamCmd(contest c){

}

void finish(contest c) {
    if (!get_certified_teams(c)) { printf("Todas as equipas foram expulsas.\n"); return; }
    if (get_treasure(c)) { printf("Ainda havia tesouros por descobrir...\n"); }
    else if (!get_treasure(c)) { printf("Todos os tesouros foram descobertos!\n"); }

    sort_teams(c);

    iterator it = contest_iterator(c);
    team a;
    while (has_next_item(it)) { 
        a = next_item(it);
        printf("%s: %d pts; %d descl.; %d com lic.", team_name(a), get_team_score(a), total_number(a) - arc_number(a), arc_number(a));
    }

    destroy_contest_elem(c);
}
void interpreter(contest c);
