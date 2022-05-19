#ifndef ARCHAEOLOGIST_H
#define ARCHAEOLOGIST_H

typedef struct _arc* arc; 

/***********************************************
newArc - Creation of the structure instance associated to the archeologist.
Parameters:

Retorno: pointer of the archeologist
Pre-condicoes:  
***********************************************/
arc newArc();

/***********************************************
destroyAcr - destroy the structure instance associated to the of the archeologist.
Parameters:
    aux - archeologist
Retorno: 
Pre-condicoes:  aux != NULL
***********************************************/
void destroyAcr(arc aux);

/***********************************************
getName - obtain the name of the archeologist.
Parameters:
    aux - archeologist
Retorno: name of archeologist
Pre-condicoes:  aux != NULL
***********************************************/
char* getName(arc aux);

/***********************************************
getCertificate - obtain the certificate of the archeologist.
Parameters:
    aux - archeologist
Retorno: certificate of archeologist
Pre-condicoes:  aux != NULL
***********************************************/
int getCertificate(arc aux);

/***********************************************
getScore - obtain the score of the archeologist.
Parameters:
    aux - archeologist
Retorno: Score of archeologist
Pre-condicoes:  aux != NULL
***********************************************/
int getScore(arc aux);

/***********************************************
getPenalty - obtain the penalty of the archeologist.
Parameters:
    aux - archeologist
Retorno: penalty of archeologist
Pre-condicoes:  aux != NULL
***********************************************/
int getPenalty(arc aux);

/***********************************************
getPos - obtain the position of the archeologist.
Parameters:
    aux - archeologist
Retorno: position of archeologist
Pre-condicoes:  aux != NULL
***********************************************/
int* getPos(arc aux);

/***********************************************
getNameGen - obtain the name of the given struct.
Parameters:
    aux - archeologist
Retorno: name of given struct
Pre-condicoes:  aux != NULL
***********************************************/
char* getNameGen(void* aux);

/***********************************************
getNewPos - add given pos to current position
Parameters:
    aux - archeologis
    c - column
    l - line
Retorno: 
Pre-condicoes:  aux != NULL
***********************************************/
void getNewPos(arc aux, int c, int l);

/***********************************************
addPenalty - add 1 to the current penalty of the archeologist
Parameters:
    aux - archeologis
    penalty - number of times the archeologist has been
Retorno: 
Pre-condicoes:  aux != NULL
***********************************************/
void addPenalty(arc aux, int penalty);

/***********************************************
addScore - add to the current score
Parameters:
    aux - archeologis
    score - score of the archeologist
Retorno: 
Pre-condicoes:  aux != NULL && score > 0
***********************************************/
void addScore(arc aux, int score);

/***********************************************
desqualify - desqualify the archeologis of the team
Parameters:
    aux - archeologis
Retorno: 
Pre-condicoes:  aux != NULL
***********************************************/
void desqualify(arc aux);

#endif //ARCHAEOLOGIST_H