#include "testy/meanValue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int meanValue(const char *path, double **dest, const int _COORDINATES)
{
    FILE *fp = fopen(path, "r");
    printf("\nTRY TO OPEN FILE ON PATH = %s\n", path);
    assert(fp != NULL && "File was not opened on path ");
    int size;
    fscanf(fp, "%d", &size);
    assert(size > 0 && "size < 0");

    //Zero value for destination array
    for (int i = 0; i < _COORDINATES; i++)
    {
        (*dest)[i] = 0;
    }

    //Read File
    int i = 0,
        j = 0,
        num = 0;
    while (fscanf(fp, "%d", &num) != EOF && i <= size * _COORDINATES)
    {
        (*dest)[j % _COORDINATES] += num;
        j++;
    }

    //Dividing sums
    for (int i = 0; i < _COORDINATES; i++)
    {
        (*dest)[i] /= size;
    }
    fclose(fp);

    return 1;
}