#include <stdio.h>
#include <stdlib.h>

#define KILO (1024)
#define MEGA (1024*1024)
#define MAX_ITEMS (64*MEGA)

#define swap(v, a, b) {unsigned tmp; tmp=v[a]; v[a]=v[b]; v[b]=tmp;}

static int *array;

static void print() {
    int i;

    for (i = 0; i < MAX_ITEMS; i++) {
        printf("%d\n", array[i]);
    }
    printf("\n");
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
    
    int i = 0;
    for(; i < 10; i++) {
    	struct timespec quickStart, quickEnd;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &mulStart);
    	quick_sort(array, 0, MAX_ITEMS-1);
    	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &mulEnd);
        printTimespec(quickStart, quickEnd, "quicksorting");
        logResult(quickStart,quickEnd);
    }
}
