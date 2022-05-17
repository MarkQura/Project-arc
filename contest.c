#include <stdlib.h>
#include "teams.h"
#include "tile.h"
#include "linkedList.h"

struct _contest {
    tile **terrain;
    int burriedTreasure;
    listaLigada teams;
};

