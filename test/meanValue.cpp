#include "gtest/gtest.h"
#include <iostream>
#include <fstream>

#define COORDINATES 3

extern "C"
{
#include "testy/meanValue.h"
#include <stdio.h>
}

TEST(meanValue, fileStreams)
{
    const char *path = "../test/test.txt";
    std::cout << "\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\nTRY TO OPEN " << path << "\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n";
    FILE *fp = fopen(path, "r");
    std::cout << "\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\nOPENED\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n";
    double *means = new double[COORDINATES];
    meanValue(fp, &means, COORDINATES);
    std::cout << "\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\nWORKED\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n";

    //Right answer
    double answer[COORDINATES] = {3, 4.4, 6.2};

    std::cout << "\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\nMEAN VALUES:\t";
    for (int i = 0; i < COORDINATES; i++)
    {
        std::cout << means[i] << ' ';
        ASSERT_TRUE(answer[i] == means[i]);
    }
    std::cout << "\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n";
    
    fclose(fp);
    delete[] means;
}