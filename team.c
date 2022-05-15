#include <stdio.h>
#include "team.h"
#include "archaeologist.h"
#include "linkedList.h"

struct _team {
    char* name;
    int merit;
    node current; //usar nextElem e verificar se tem certificado se nao voltar para head da lista
    archaeologist star;
    linkedList archaeologists;
};