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
    const char *path = "../../test/test.txt";
    double *means = new double[COORDINATES];
    meanValue(path, &means, COORDINATES);

    //Right answer
    double answer[COORDINATES] = {3, 4.4, 6.2};

    std::cout << "\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\nMEAN VALUES:\t";
    for (int i = 0; i < COORDINATES; i++)
    {
        std::cout << means[i] << ' ';
        ASSERT_TRUE(answer[i] == means[i]);
    }
    printf("\n");

    delete[] means;
}