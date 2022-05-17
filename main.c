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

    sscanf(buffer, "%d %d", &C, &L);
    contest c = new_contest(C, L);
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < L;) {
            ch = fgetc(stdin);
            if (ch == ' ' || ch == '\n' || ch == EOF) {
                set_tile_treasure(c, i, j, aux);
                j++;
                aux = 0;
            }
            aux = aux*10 + (ch - '0');
        }
    }
    return c;
}

void interpreter(contest c) {

}

void team_star(contest c, char* name) {
    iterator it = contest_iterator(c);
    team aux;

    while (has_next_item(it)) {
        aux = next_item(it);
        if (!strcmp(team_name(aux), name)) {
            destroy_iterator(it);
        }
    }
}