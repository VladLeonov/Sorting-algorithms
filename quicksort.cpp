#include "quicksort.h"
#include <algorithm>


using namespace std;


int partition(int *array, int leftIndex, int rightIndex) {
	swap(array[(leftIndex + rightIndex) / 2], array[rightIndex]);
	int x = array[rightIndex];
	int i = leftIndex - 1;
	for (int j = leftIndex; j < rightIndex; j++) {
		if (array[j] <= x) {
			i++;
			swap(array[i], array[j]);
		}
	}
	swap(array[i + 1], array[rightIndex]);
	return i + 1;
}


void quicksort(int *array, int leftIndex, int rightIndex) {
	if (leftIndex < rightIndex) {
		int center = partition(array, leftIndex, rightIndex);
		quicksort(array, leftIndex, center - 1);
		quicksort(array, center + 1, rightIndex);
	}
}
