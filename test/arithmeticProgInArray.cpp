#include "gtest/gtest.h"

extern "C" {
#include "testy/arithmeticProgInArray.h"
}

//All right
TEST(arithmeticalProgInArray, ok) {
    int size = 10;
    int* arr = new int[size];
	int* dist;
	int arr2[] = { 1, 2, 3, -6, 9, 10, 11, 12, 13, 14 };
	for (int i = 0; i < size; i++)
	{
		arr[i] = arr2[i];
	}
	int dist_size = arithmeticProgInArray(arr, &dist, size);
    ASSERT_EQ(dist_size, 6);
	EXPECT_EQ(dist, arr + 4);
	for (int i = 0; i < dist_size; i++)
	{
		ASSERT_EQ(dist[i], arr[i + 4]);
	}
	
	int delta = dist[1] - dist[0];
	for (int i = 1; i < dist_size; i++)
	{
		delta = dist[i] - dist[i - 1]; 
	}
	EXPECT_EQ(delta, dist[1] - dist[0]);
    delete[] arr;
}

//Negative size
TEST(nagativeSizeInArray, fault) {
    int size = 10;
    int* arr = new int[size];
	int* dist;
	int arr2[] = { 1, 2, 3, -6, 9, 10, 11, 12, 13, 14 };
	for (int i = 0; i < size; i++)
	{
		arr[i] = arr2[i];
	}
    ASSERT_DEATH(arithmeticProgInArray(arr, &dist, -3), "size > 0");
    delete[] arr;
}

//All array is a progressive
TEST(allArrayIsProgressive, all) {
    int size = 10;
    int* arr = new int[size];
	int* dist;
	for (int i = 0; i < size; i++)
	{
		arr[i] = i;
	}
	int dist_size = arithmeticProgInArray(arr, &dist, size);
    ASSERT_EQ(dist_size, size);
	EXPECT_EQ(dist, arr);
	for (int i = 0; i < dist_size; i++)
	{
		ASSERT_EQ(dist[i], arr[i]);
	}
	
	int delta = dist[1] - dist[0];
	for (int i = 1; i < dist_size; i++)
	{
		delta = dist[i] - dist[i - 1]; 
	}
	EXPECT_EQ(delta, dist[1] - dist[0]);
    delete[] arr;
}

//Two elements in array
TEST(twoElementsInArray, two) {
    int size = 2;
    int* arr = new int[size];
	int* dist;
	int arr2[] = { 1, 8};
	for (int i = 0; i < size; i++)
	{
		arr[i] = arr2[i];
	}
	int dist_size = arithmeticProgInArray(arr, &dist, size);
    ASSERT_EQ(dist_size, size);
	EXPECT_EQ(dist, arr);
	for (int i = 0; i < dist_size; i++)
	{
		ASSERT_EQ(dist[i], arr[i]);
	}
	
	int delta = dist[1] - dist[0];
	for (int i = 1; i < dist_size; i++)
	{
		delta = dist[i] - dist[i - 1]; 
	}
	EXPECT_EQ(delta, dist[1] - dist[0]);
    delete[] arr;
}