#include "heapsort.h"
#include <algorithm>


using namespace std;


void maxHeapify(int *array, int index, int heapSize) {
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int largest;
	if ((left < heapSize) && (array[left] > array[index])) {
		largest = left;
	} else {
		largest = index;
	}
	if ((right < heapSize) && (array[right] > array[largest])) {
		largest = right;
	}
	if (largest != index) {
		swap(array[index], array[largest]);
		maxHeapify(array, largest, heapSize);
	}	
}

void buildMaxHeap(int *array, int arraySize) {
	for (int i = arraySize / 2; i >= 0; i--) {
		maxHeapify(array, i, arraySize);
	}
}

void heapsort(int *array, int arraySize) {
	int heapSize = arraySize;
	buildMaxHeap(array, arraySize);
	for (int i = arraySize - 1; i > 0; i--) {
		swap(array[0], array[i]);
		heapSize--;
		maxHeapify(array, 0, heapSize);
	}
}
