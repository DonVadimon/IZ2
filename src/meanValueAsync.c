#include "testy/meanValueAsync.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/mman.h>

void meanValueAsync(FILE *fp, double **dest, const int _COORDINATES)
{
    int d = get_nprocs();
    int pid = getpid();
    printf("\nProcessors: %d\nPID: %d\n\n", d, pid);
}