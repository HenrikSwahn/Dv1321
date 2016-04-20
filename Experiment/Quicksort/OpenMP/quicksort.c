/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define KILO (1024)
#define MEGA (1024*1024)
//#define MAX_ITEMS (64*MEGA)
#define MAX_ITEMS 100
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

    #pragma omp parallel for
    for (;low <= high;) {
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

    #pragma omp parallel sections 
    {
	    if (low < pivot)
	    	#pragma omp section
	        quick_sort(array, low, pivot-1);
	    if (pivot < high)
	    	#pragma omp section
	        quick_sort(array, pivot+1, high);
	}
}

int main(int argc, char **argv) {
    
    int i = 0;
    removeResultFile();
    //for(; i < 10; i++) {
    	init();
    	struct timespec quickStart, quickEnd;
        clock_gettime(CLOCK_REALTIME, &quickStart);
    	quick_sort(array, 0, MAX_ITEMS-1);
    	clock_gettime(CLOCK_REALTIME, &quickEnd);
        printTimespec(quickStart, quickEnd, "quicksorting");
        logResult(quickStart,quickEnd);
    //}
	//logOrder(array, MAX_ITEMS);
}*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define KILO (1024)
#define MEGA (1024*1024)
//#define MAX_ITEMS (64*MEGA)
#define MAX_ITEMS 100
#define swap(v, a, b) {unsigned tmp; tmp=v[a]; v[a]=v[b]; v[b]=tmp;}

static int *v;

int partition(int * a, int p, int r) {
    int lt[r-p];
    int gt[r-p];
    int i;
    int j;
    int key = a[r];
    int lt_n = 0;
    int gt_n = 0;

	#pragma omp parallel for
    for(i = p; i < r; i++) {
        if(a[i] < a[r]) {
            lt[lt_n++] = a[i];
        }
        else {
            gt[gt_n++] = a[i];
        }   
    }   

    for(i = 0; i < lt_n; i++){
        a[p + i] = lt[i];
    }   

    a[p + lt_n] = key;

    for(j = 0; j < gt_n; j++){
        a[p + lt_n + j + 1] = gt[j];
    }   

    return p + lt_n;
}

void quicksort(int * a, int p, int r) {
    int div;

    if(p < r) { 
        div = partition(a, p, r); 
		#pragma omp parallel sections
        {   
			#pragma omp section
            quicksort(a, p, div - 1); 
			#pragma omp section
            quicksort(a, div + 1, r); 

        }
    }
}

void init() {
    int i;
    v = (int *) malloc(MAX_ITEMS*sizeof(int));
    for (i = 0; i < MAX_ITEMS; i++) {
        array[i] = rand();
	}
}

static void print() {
    int i;

    for (i = 0; i < MAX_ITEMS; i++) {
        printf("%d\n", v[i]);
    }
    printf("\n");
}

int main() {
	init();
    quicksort(v, 0, MAX_ITEMS-1);
    print();
    return 0;
}