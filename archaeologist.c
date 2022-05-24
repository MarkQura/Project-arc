#include <stdlib.h>
#include <string.h>

#include "archaeologist.h"

struct _arc
{
    char name[50];
    int score, certeficate, penalty;
    int pos[2];
};

arc newArc(char *name)
{
    arc aux = (arc)malloc(sizeof(struct _arc));
    if (aux == NULL)
        return NULL;
    strncpy(aux->name, name, sizeof(aux->name));
    aux->score = 0;
    aux->certeficate = 1;
    aux->pos[0] = -1;
    aux->pos[1] = -1;
    return aux;
}

void destroyArc(arc aux)
{
    free(aux);
}

void destroyArcGen(void *aux)
{
    destroyArc((arc)aux);
}

char *getName(arc aux)
{
    return aux->name;
}

int getCertificate(arc aux)
{
    return aux->certeficate;
}

int getScore(arc aux)
{
    return aux->score;
}

int getPenalty(arc aux)
{
    return aux->penalty;
}

int *getPos(arc aux)
{
    return aux->pos;
}

char *getNameGen(void *aux)
{
    return getName((arc)aux);
}

void getNewPos(arc aux, int c, int l)
{
    aux->pos[0] += c;
    aux->pos[1] += l;
}

void addScore(arc aux, int score)
{
    aux->score += score;
}

void addPenalty(arc aux)
{
    ++aux->penalty;
}

void desqualify(arc aux)
{
    aux->certeficate = 0;
}