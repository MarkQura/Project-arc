#include <stdio.h>
#include <stdlib.h>
#include "contest.h"
#include "team.h"
#include "iterator.h"

contest make_contest();

int main() {
    contest c = make_contest();
    interpreter(c);
    destroy_contest(c);
    return 1;
}

contest make_contest() {
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

void interpreter(contest c){

}

void buriedRichness(contest c){
    printf("%d", getCurrentRichness(c));
}

void team_star(contest c, char* buffer) {

    char name[40];
    sscanf(buffer, "estrela %40[^\n]", name);

    team t = has_team(c, name);
    if (t == NULL) { printf("Equipa invalida\n"); return; }

    printf("Star%s: %s", team_name(t), arcName(get_star(t)));
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

void finish(contest c) {
    if (!get_certified_elems(c)) { printf("Todas as equipas foram expulsas.\n"); return; }
    if (get_treasure(c)) { printf("Ainda havia tesouros por descobrir...\n"); }
    else if (!get_treasure(c)) { printf("Todos os tesouros foram descobertos!\n"); }


}