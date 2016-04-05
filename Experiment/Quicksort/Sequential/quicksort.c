#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init(int[], int);
void quicksort(int[], int, int);
void print(int[], int);
int partition(int[], int, int);
void swap(int[], int, int);
int pivotIndex(int, int);

int main(int argc, char *argv[]) {

	srand((unsigned) time(NULL));
	
	int size = atoi(argv[1]);
	int array[size];
	
	init(array, size);

	//Unsorted
	print(array, size);
	
	quicksort(array, 0, size-1);

	//Sorted
	print(array, size);
}

void init(int array[], int size) {

	int i = 0;
	for(; i < size; i++) {
		array[i] = rand() % 10;
	}
}

void print(int array[], int size) {

	int i = 0;
	for(; i < size; i++) {
		printf("%d\n", array[i]);
	}

	printf("\n");
}

void quicksort(int array[], int left, int right) {

	if(left < right) {
		int p = partition(array, left, right);
		quicksort(array, left, p);
		quicksort(array, p+1, right);
	}
}

int partition(int array[], int left, int right) {

	int pi = pivotIndex(left, right);
	int pivot = array[pi];
	int i = left - 1;
	int j = right + 1;
	do {
		do {
			i++;
		} while(array[i] < pivot);

		do {
			j--;
		} while(array[j] > pivot);

		if (i >= j) {
			return j;
		}

		swap(array, i, j);

	} while(1);
}

void swap(int array[], int from, int to) {

	int temp = array[to];
	array[to] = array[from];
	array[from] = temp;

}

int pivotIndex(int left, int right) {
	return ((right - left) / 2) + left;
}

