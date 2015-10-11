#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#define INPUT_SIZE 8

#include IMPL

#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    /* build the entry */
    indexTable e;
    e.iEntrys = malloc(sizeof(entry)*MAXSIZE);
#if defined(__GNUC__)
    __builtin___clear_cache(&e, &e + sizeof(entry)*MAXSIZE);
#endif
    printf("size of entry : %lu bytes\n", sizeof(entry));


    clock_gettime(CLOCK_REALTIME, &start);
    buildIndexTable(&e,fp);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);


    /* the givn last name to find */
    char input[INPUT_SIZE][MAX_LAST_NAME_SIZE] = {"uninvolved","zyxel","whiteshank",
            "odontomous", "pungoteague", "reweighted", "xiphisternal", "yakattalo"
                                                 };

    assert(findName(input[0], &e, fp) &&
           "Did you implement findName() in " IMPL "?");

#if defined(__GNUC__)
    __builtin___clear_cache(&e, &e + sizeof(entry)*MAXSIZE);
#endif
    /* compute the execution time */
    int j;
    clock_gettime(CLOCK_REALTIME, &start);
    for(j = 0; j < INPUT_SIZE; j++) {
        findName(input[j], &e, fp);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);

    /* FIXME: release all allocated entries */
    fclose(fp);

    return 0;
}
