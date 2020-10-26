#include "testy/arithmeticProgInArray.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Введите размер массива\n");
  int size = 0;
	scanf("%d", &size);
	int* arr = malloc(size * sizeof(int));
	int* dist;
	//int arr2[] = { 1, 2, 3, -6, 9, 10, 11, 12, 13, 14 };
	
  printf("Введите сам массив\n");
	for (int i = 0; i < size; i++)
	{
		scanf("%d", &arr[i]);
	}

  printf("Введенный массив\n");
	for (int i = 0; i < size; i++)
	{
    printf("%d ", arr[i]);
	}
  printf("\n");

	int dist_size = arithmeticProgInArray(arr, &dist, size);

	printf("Максимальная последовательность, являющаяся арифметической прогрессией\n");
	for (int i = 0; i < dist_size; i++)
	{
    printf("%d ", dist[i]);
	}
  printf("\n");
  free(arr);
  return 0;
}