#include <stdio.h>
#include <stdlib.h>

#define KILO (1024)
#define MEGA (1024*1024)
#define MAX_ITEMS (64*MEGA)

#define swap(v, a, b) {unsigned tmp; tmp=v[a]; v[a]=v[b]; v[b]=tmp;}

<<<<<<< HEAD
static int *array;

static void print() {
    int i;

    for (i = 0; i < MAX_ITEMS; i++) {
        printf("%d\n", array[i]);
    }
    printf("\n");
=======
	srand((unsigned) time(NULL));
	
	long size = atoi(argv[1]);
	removeResultFile();
	
	int i;
	for(i = 0; i < 10; i++) {
		
		int * array = malloc(size * sizeof(int));
		init(array, size);

		//Unsorted
		if(size < 32) {
			print(array, size);
		}
	
		struct timespec quickStart, quickEnd;
	        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &quickStart);	
		quicksort(array, 0, size-1);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &quickEnd);
       		printTimespec(quickStart, quickEnd, "quicksort");
        	logResult(quickStart,quickEnd);

		//Sorted
		if(size < 32) {
			print(array, size);
		}
		free(array);
	}
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
>>>>>>> 923a7ff937a383ca366c590914a7fe8194299ce4
}

static void init() {
    int i;

    array = (int *) malloc(MAX_ITEMS*sizeof(int));
    for (i = 0; i < MAX_ITEMS; i++) {
        array[i] = rand();
	}
}

static unsigned partition(int *array, unsigned low, unsigned high, unsigned pivot_index) {

    if (pivot_index != low)
        swap(array, low, pivot_index);

    pivot_index = low;
    low++;

    while (low <= high) {
        if (array[low] <= array[pivot_index])
            low++;
        else if (array[high] > array[pivot_index])
            high--;
        else
            swap(array, low, high);
    }

    if (high != pivot_index)
        swap(array, pivot_index, high);
    return high;
}

static void quick_sort(int *array, unsigned low, unsigned high) {
    
    unsigned pivot;
    
    if (low >= high)
        return;
    pivot = (low+high)/2;
    pivot = partition(array, low, high, pivot);

    if (low < pivot)
        quick_sort(array, low, pivot-1);
    if (pivot < high)
        quick_sort(array, pivot+1, high);
}

int main(int argc, char **argv) {
    init();
    removeOrderFile();
    quick_sort(array, 0, MAX_ITEMS-1);
    logOrder(array, MAX_ITEMS);
}
