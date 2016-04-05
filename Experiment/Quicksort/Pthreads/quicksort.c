#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void init(int[], int);
void quicksort(int[], int, int);
void print(int[], int);
int partition(int[], int, int);
void swap(int[], int, int);
int pivotIndex(int, int);
void * worker(void *);
int requiredSorts(int);

typedef struct {
	int left;
	int right;
	int *arr;
} Args;

int main(int argc, char *argv[]) {

	srand((unsigned) time(NULL));
	
	int size = atoi(argv[1]);
	int nrOfThreads = atoi(argv[2]);
	int nrOfSorts = requiredSorts(nrOfThreads);
	int threadCounter = 0;
	int requiredThreads = nrOfThreads;

	int array[size];
	pthread_t tid[nrOfThreads];

	init(array, size);
	
	//Unsorted
	print(array, size);
	
	int i = 0, maxSize;
	maxSize = size / nrOfThreads;
	int left = 0, right = maxSize;

	while(requiredThreads >= 1) {
		Args *args = malloc(sizeof(Args));
		args->left = left;
		args->right = right;
		args->arr = array;
		pthread_create(&tid[threadCounter++], 0, worker, args);

		left += maxSize;
		right += maxSize;

		if(threadCounter == requiredThreads) {
			for(i = 0; i < nrOfThreads; i++) {
				pthread_join(tid[i], NULL);
			}
			threadCounter = 0;
			requiredThreads = requiredThreads / 2;
			maxSize = maxSize += maxSize;
			left = 0;
			right = maxSize;
		}
	}

	//Sorted
	print(array, size);
}

void * worker(void *arg) {
	Args args = *((Args*)arg);
	quicksort(args.arr, args.left, args.right-1);
	free(arg);
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

int requiredSorts(int threads) {

	switch(threads) {
		case 2:
			return 3;
		case 4:
			return 7;
		case 8:
			return 15;
	}
}