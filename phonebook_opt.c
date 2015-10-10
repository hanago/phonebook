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
    i = 0;
    do {
        if(i >= MAXSIZE || (!fgets(line,MAX_LAST_NAME_SIZE,fp)))
            break;
        if(line[0] == '\n')
            continue;
        (iTable->iEntrys+i)->index = i == 0 ? 0 :
                                     ftell(fp) - strlen(line) - 1;
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
        cursor = (lowerBound+upperBound)/2;
        fseek(fp, (iTable->iEntrys+cursor)->index, SEEK_SET);
        fscanf(fp, "%s", line);

        /* binary search */
        diff = strcasecmp(lastName, line);
        if(diff == 0) {
            printf(" %12s  is found!\n", lastName);
            return (iTable->iEntrys+cursor)->index;
        } else if(diff > 0)
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
