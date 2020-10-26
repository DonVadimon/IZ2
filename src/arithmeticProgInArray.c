#include "testy/arithmeticProgInArray.h"
#include <assert.h>

int arithmeticProgInArray(int* source, int** dist, int size)
{
	assert(size > 0);
	if (size == 2)
	{
		(*dist) = source;
		return 2;
	}
	
	int delta = source[1] - source[0];
	int subSize = 0;
	int tmpSize = 2;
	(*dist) = source;
	for (int i = 2; i < size; ++i) {
		if (delta == (source[i] - source[i - 1]))
		{
			tmpSize++;
		}
		else if (tmpSize > subSize)
		{
			subSize = tmpSize;
			(*dist) = source + i - subSize;
			delta = source[i] - source[i - 1];
			tmpSize = 2;
		}
		else
		{
			delta = source[i] - source[i - 1];
			tmpSize = 2;
		}
	}
	if (tmpSize > subSize)
	{
		subSize = tmpSize;
		(*dist) = source + size - subSize;
	}
	return subSize;
}