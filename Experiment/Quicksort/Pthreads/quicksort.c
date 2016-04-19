/***************************************************************************
 *
 * MultiThreaded version of Quick sort
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define KILO (1024)
#define MEGA (1024*1024)
#define MAX_ITEMS (64*MEGA)
//#define MAX_ITEMS 64
#define MAX_THREADS 8
#define SET_SIZE (MAX_ITEMS/MAX_THREADS)
#define swap(v, a, b) {unsigned tmp; tmp=v[a]; v[a]=v[b]; v[b]=tmp;}

static int *v;

pthread_t tid[MAX_THREADS];
typedef struct {
	int end;
	int start;	
} Args;

void * sortWorker(void * args);

static void print_array(void) {
    int i;
	
	for(i = 0; i < MAX_ITEMS; i++) {	       	 
		if(i % 8 == 0) { 
		//	printf("---\n");
		}
		printf("%d\n", v[i]);
	}

    printf("\n");
}

static void init_array(void) {
    	int i;

	v = (int *) malloc (MAX_ITEMS*sizeof(int));
	for (i = 0; i < MAX_ITEMS; i++) {
		v[i] = rand();
	}	
}

static unsigned partition(int *v, unsigned low, unsigned high, unsigned pivot_index) {
    /* move pivot to the bottom of the vector */
    if (pivot_index != low)
        swap(v, low, pivot_index);

    pivot_index = low;
    low++;

    /* invariant:
     * v[i] for i less than low are less than or equal to pivot
     * v[i] for i greater than high are greater than pivot
     */

    /* move elements into place */
    while (low <= high) {
        if (v[low] <= v[pivot_index])
            low++;2
        else if (v[high] > v[pivot_index])
            high--;
        else
            swap(v, low, high);
    }

    /* put pivot back between two groups */
    if (high != pivot_index)
        swap(v, pivot_index, high);
    return high;
}

static void quick_sort(int *v, unsigned low, unsigned high) {
    unsigned pivot_index;
    
    /* no need to sort a vector of zero or one element */
    if (low >= high)
        return;

    /* select the pivot value */
    pivot_index = (low+high)/2;

    /* partition the vector */
    pivot_index = partition(v, low, high, pivot_index);

    /* sort the two sub arrays */
    if (low < pivot_index)
        quick_sort(v, low, pivot_index-1);
    if (pivot_index < high)
        quick_sort(v, pivot_index+1, high);
}

void * sortWorker(void * arg) {
	
	Args args = *((Args *) arg);
	quick_sort(v, args.start, args.end-1);	
	free(arg);
	pthread_exit(0);
	
}

/* ----------------------------------------------------------------*/

typedef struct {
	unsigned leftStart;
	unsigned rightStart;
	unsigned setSize;
} MergeArgs;

void * mergeWorker(void * arg) {
	
	MergeArgs args = *((MergeArgs *) arg);	
	int * left = v + args.leftStart;
	int * right = v + args.rightStart;
	int * temp = malloc((args.setSize * 2)*sizeof(int));
	int size = args.setSize;
	int i,j,k;
	i = j = k = 0;
	while(i < size && j < size) {
		if(left[i] <= right[j]) {
			temp[k++] = left[i++];
		}	
		else {
			temp[k++] = right[j++];
		}
	}
	while(i < size) 
		temp[k++] = left[i++];
	while(j < size)
		temp[k++] = right[j++];	

	i = 0;
	int s = args.leftStart;
	for(; i < args.setSize * 2; i++) {
		v[s++] = temp[i];
	}
	free(arg);
	free(temp);
	pthread_exit(0);
}

/*-----------------------------------------------------------------*/
int main(int argc, char **argv) {
    init_array();
	int i = 0;
	for(; i < MAX_THREADS; i++) {
		Args * args = malloc(sizeof(* args));
		args->start = SET_SIZE * (i+1) - SET_SIZE;
		args->end = SET_SIZE * (i+1);
		pthread_create(&tid[i], 0, sortWorker, args);
	}
	i = 0;
	for(; i < MAX_THREADS; i++) {
		pthread_join(tid[i], NULL);
	}
	
	i = 0;
	for(; i < MAX_THREADS/2; i++) {
		if(i == 0) {
			MergeArgs * args = malloc(sizeof(* args));
            args->leftStart = 0;
            args->rightStart = SET_SIZE;
            args->setSize = SET_SIZE;
			pthread_create(&tid[i], 0, mergeWorker, args);

		}
		else if(i == 1) {	
			MergeArgs * args = malloc(sizeof(* args));
			args->leftStart = SET_SIZE * 2;
			args->rightStart = SET_SIZE * 3;
			args->setSize = SET_SIZE;
			pthread_create(&tid[i], 0, mergeWorker, args);
		}
		else if(i == 2) {
			MergeArgs * args = malloc(sizeof(* args));
			args->leftStart = SET_SIZE * 4;
			args->rightStart = SET_SIZE * 5;
			args->setSize = SET_SIZE;
			pthread_create(&tid[i], 0, mergeWorker, args);
		}
		else {	
			MergeArgs * args = malloc(sizeof(* args));
			args->leftStart = SET_SIZE * 6;
			args->rightStart = SET_SIZE * 7;
			args->setSize = SET_SIZE;
			pthread_create(&tid[i], 0, mergeWorker, args);
		}
	}	
	
	i = 0;
	for(; i < MAX_THREADS/4; i++) {
		pthread_join(tid[i], NULL);
	}

	i = 0;
	for(; i < MAX_THREADS/4; i++) {
		if(i==0) {	
			MergeArgs * args = malloc(sizeof(* args));
			args->leftStart = 0;
			args->rightStart = SET_SIZE * 2;
			args->setSize = SET_SIZE * 2;
			pthread_create(&tid[i], 0, mergeWorker, args);
		}
		else {	
			MergeArgs * args = malloc(sizeof(* args));
			args->leftStart = SET_SIZE * 4;
			args->rightStart = SET_SIZE * 6;
			args->setSize = SET_SIZE * 2;
			pthread_create(&tid[i], 0, mergeWorker, args);
		}

	}
	i = 0;
	for(; i < MAX_THREADS/4; i++) {
		pthread_join(tid[i], NULL);
	}

	i = 0;	
	MergeArgs * args = malloc(sizeof(* args));
	args->leftStart = 0;
	args->rightStart = SET_SIZE * 4;
	args->setSize = SET_SIZE * 4;
	pthread_create(&tid[0], 0, mergeWorker, args);
	pthread_join(tid[0], NULL);
}

