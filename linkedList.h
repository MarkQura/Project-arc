typedef struct _linkedList* linkedList; 

linkedList newList();

void destroyList();

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
