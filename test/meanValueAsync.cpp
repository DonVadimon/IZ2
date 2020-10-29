#include "gtest/gtest.h"
#include <iostream>

#define COORDINATES 3

extern "C"
{
#include "testy/meanValueAsync.h"
#include <stdio.h>
}

TEST(meanValueAsync, t)
{
    // const char *path = "../test/test.txt";
    // FILE *fp = fopen(path, "r");
    // std::cout << "\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\nTRY TO OPEN " << path << "\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n";
    // assert(fp != NULL);
    // std::cout << "\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\nOPENED\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n";
    // double *means = new double[COORDINATES];

    // meanValueAsync(fp, &means, COORDINATES);

    // fclose(fp);
    // delete[] means;
}