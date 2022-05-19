#include <stdlib.h>
#include "archaeologist.h"

struct _arc{
    char name[40];
    int score, certeficate, penalty;
    int pos[2];
};

arc newArc(){
    arc aux = (arc)malloc(sizeof(struct _arc));
    if (aux == NULL)
        return NULL;
    aux->score = 0;
    aux->certeficate = 1;
    aux->penalty = 0;
    aux->pos[0] = -1;
    aux->pos[1] = -1;
    return aux;
}

void destroyArc(arc aux){
    free(aux);
}

char *getName(arc aux){
    return aux->name;
}

int getCertificate(arc aux){
    return aux->certeficate;
}

int getScore(arc aux){
    return aux->score;
}

int getPenalty(arc aux){
    return aux->penalty;
}

int *getPos(arc aux){
    return aux->pos;
}

char *getNameGen(void *aux){
    return getName((arc)aux);
}

void getNewPos(arc aux, int c, int l){
    aux->pos[0] += c;
    aux->pos[1] += l;
}

void addPenalty(arc aux){
    aux->penalty++;
}

void addScore(arc aux, int score){
    aux->score += score;
}

void desqualify(arc aux){
    aux->certeficate = 0;
}