typedef struct _linkedList* linkedList; 

linkedList newList();

void destroyList();

void destroyListAndElems(linkedList list, void (*destroy)(void *));

void addHead();

void insert();

void append();

int sizeList();

int sizeBanned();

int sizeCertified();

iterator BannedIterator();

iterator certifiedIterator();

void moveToTail();

void moveToIndex();
