#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define KILO (1024)
#define MEGA (1024*1024)
#define MAX_ITEMS 10000000
#define MAX_THREAD 8

#define swap(v, a, b) {unsigned tmp; tmp=v[a]; v[a]=v[b]; v[b]=tmp;}

void quicksort(int *, unsigned, unsigned, unsigned);

typedef struct {
        int *array;	
        unsigned low;
        unsigned high;
        unsigned lim;
} Args;

static void print(int * array) {
    int i;

    for (i = 0; i < MAX_ITEMS; i++)
        printf("%d \n", array[i]);
    printf("\n");
}

int * init() {
    int i;
    int * a  = (int *) malloc(MAX_ITEMS*sizeof(int));
    for (i = 0; i < MAX_ITEMS; i++)
        a[i] = rand() % 10;
    return a;
}

unsigned partition(int *array, unsigned low, unsigned high, unsigned pivot_index) {
 
    if (pivot_index != low) {
	 swap(array, low, pivot_index);
	}	

    pivot_index = low;
    low++;

    while (low <= high) {
        if (array[low] <= array[pivot_index]) low++;
        else if (array[high] > array[pivot_index]) high--;
        else swap(array, low, high);
    }

    if (high != pivot_index) {
	 swap(array, pivot_index, high);
	}

    return high;
}

void* worker(void *arg) {
	Args *args = arg;
	quicksort(args->array, args->low, args->high, args->lim);
	free(args);
	pthread_exit(0);
}

void quicksort(int *array, unsigned low, unsigned high, unsigned limit) {
	if(low >= high) return;

	unsigned pivot_index = (low + high)/2;
	pivot_index = partition(array, low, high, pivot_index);

	if (limit-- > 0) {
		pthread_t thread;

		if (low < pivot_index) {
			Args * args = malloc(sizeof(Args));
			args->array = array;
			args->low = low;
			args->high = pivot_index - 1;
			args->lim = limit;
			pthread_create(&thread, NULL, worker, args);
		}
		quicksort(array, pivot_index + 1, high, limit);
		pthread_join(thread, NULL);
	} 
	else {
		quicksort(array, low, pivot_index - 1,  0);
		quicksort(array, pivot_index + 1, high, 0);
	}
}

int main(int argc, char **argv) {
	srand((unsigned) time(NULL));
    	int * array = init();

	//print(array);
    	quicksort(array, 0, MAX_ITEMS-1, (unsigned)log2(MAX_THREAD));
	//print(array);
	free(array);
}
