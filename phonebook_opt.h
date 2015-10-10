#ifndef _PHONEBOOK_BINARY_H
#define _PHONEBOOK_BINARY_H
#include <stdio.h>
#include <stdint.h>
#define MAX_LAST_NAME_SIZE 16

/* binary search version */
#define MAXSIZE 10000000
typedef struct {
    int index;
} entry;

typedef struct {
    entry* iEntrys;
    int size;
} indexTable;

int buildIndexTable(indexTable* iTable, FILE* fp);
entry *findName(char lastName[], indexTable *iTable, FILE* fp);

#endif
