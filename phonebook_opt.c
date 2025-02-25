#include <stdlib.h>
#include <stdio.h>
#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
int buildIndexTable(indexTable* iTable, FILE* fp)
{
    /* load words from a sorted dictionary */
    int i;
    char line[MAX_LAST_NAME_SIZE];

    iTable->iEntrys = malloc(sizeof(entry)*MAXSIZE);

    /* first entry*/
    (iTable->iEntrys)->index = 0;
    if((!fgets(line,MAX_LAST_NAME_SIZE,fp))) {
        iTable->size = 0;
        return 0;
    }

    /* rest of entries */
    i = 1;
    do {
        if(i >= MAXSIZE || (!fgets(line,MAX_LAST_NAME_SIZE,fp)))
            break;
        if(line[0] == '\n')
            continue;
        /** Locate the index of the string at the file stream. **/
        /* ftell(fp): current index of the file stream.*/
        (iTable->iEntrys+i)->index = ftell(fp) - strlen(line) - 1;
        i = i+1;
    } while(1);
    iTable->size = i;
    return 0;
}

entry *findName(char lastName[], indexTable *iTable, FILE* fp)
{
    /* find the string by binary search */
    int cursor, diff = 0, lowerBound = 0, upperBound = iTable->size;
    char line[MAX_LAST_NAME_SIZE];

    while (lowerBound < upperBound) {
        /* get the string of index from the file stream */
        cursor = lowerBound + (upperBound - lowerBound) / 2;
        fseek(fp, (iTable->iEntrys+cursor)->index, SEEK_SET);
        fscanf(fp, "%s", line);

        /* binary search */
        diff = strcasecmp(lastName, line);
        if(diff == 0) 
            return (iTable->iEntrys+cursor)->index;
        else if(diff > 0)
            lowerBound = lowerBound + (upperBound-lowerBound)/2 + 1;
        else
            upperBound = upperBound - (upperBound-lowerBound)/2;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    return NULL;
}
