#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <string>
#include <sstream>

#include "quicksort.h"
#include "heapsort.h"
#include "gnuplot.h"


using namespace std;


int measureTimeOfSorting(void (*sortMethod)(int*, int), int *array, int arraySize) {
	int startTime, endTime;
	startTime = clock();
    sortMethod(array, arraySize);
    endTime = clock();
    return endTime - startTime;
}


static int intCompare(const void *p1, const void *p2) {
	int left =	*(const	int *)p1;
	int right = *(const int *)p2;
	return ((left > right) - (left < right));
}


void callStdSort(int *array, int arraySize) {
	sort(array, array + arraySize);
}


void callQsort(int *array, int arraySize) {
	qsort(array, arraySize, sizeof(int), intCompare);
}


void callQuicksort(int *array, int arraySize) {
	quicksort(array, 0, arraySize - 1);
}


void callHeapsort(int *array, int arraySize) {
	heapsort(array, arraySize);
}


void addPlotValuesToStream(void (*sortMethod)(int*, int), ostringstream &valuesStream, bool isAlmostSorted) {
	for (int size = 250000; size > 5000; size -= size / 10) {
		int array[size];
		if (isAlmostSorted == true) {
			for (int i = 0; i < size; i++) {
				array[i] = i + rand() % 10;
			}
		} else {
			for (int i = 0; i < size; i++) {
				array[i] = rand() % size;
			}
		}
		valuesStream << size / 1000 << " " << measureTimeOfSorting(sortMethod, array, size) << endl;
	}
	valuesStream << "e" << endl;
}


int main(int argc, char** argv) {
	
	srand(time(0));
	
	Gnuplot plot;
	plot("set multiplot layout 1, 2 title \"Runtime of sorting algorithms\"");
	plot("set xlabel \"Array size, thous.\"");
	plot("set ylabel \"Runtime, ms\"");
	plot("set xrange [ 0 : 250 ]");
	plot("set yrange [ 0 : 100 ]");
	plot("set key left");
	
	plot("set title \"Random values\"");
	plot("plot '-' title \"std::sort\" with lines, "
			  "'-' title \"std::qsort\" with lines, "
			  "'-' title \"quicksort\" with lines, "
			  "'-' title \"heapsort\" with lines");
			  
	ostringstream valuesStream;
	addPlotValuesToStream(callStdSort, valuesStream, false);
	addPlotValuesToStream(callQsort, valuesStream, false);
	addPlotValuesToStream(callQuicksort, valuesStream, false);
	addPlotValuesToStream(callHeapsort, valuesStream, false);
	plot(valuesStream.str());
	
	plot("set title \"Almost sorted values\"");
	plot("unset ylabel");
	plot("plot '-' title \"std::sort\" with lines, "
			  "'-' title \"std::qsort\" with lines, "
			  "'-' title \"quicksort\" with lines, "
			  "'-' title \"heapsort\" with lines");
	
	valuesStream.str("");
	valuesStream.clear();
	addPlotValuesToStream(callStdSort, valuesStream, true);
	addPlotValuesToStream(callQsort, valuesStream, true);
	addPlotValuesToStream(callQuicksort, valuesStream, true);
	addPlotValuesToStream(callHeapsort, valuesStream, true);
	plot(valuesStream.str());
	
	plot("unset multiplot");
	
	system("pause");
	return 0;
}
