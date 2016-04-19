/*#include <stdio.h>
#include <stdlib.h>

#define KILO (1024)
#define MEGA (1024*1024)
#define MAX_ITEMS 32
#define THREADS 4
#define SET (MAX_ITEMS/THREADS)
#define swap(v, a, b) {unsigned tmp; tmp=v[a]; v[a]=v[b]; v[b]=tmp;}

pthread_t threads[THREADS];

typedef struct {
	int low;
	int high;
	int *arr;
} Args;

typedef struct {
	unsigned leftStart;
	unsigned rightStart;
	unsigned setSize;
	int * array;
} ArgsM;

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
        array[i] = rand() % 10;
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

void * worker(void * args) {
	Args argument = *((Args*)args);
	quick_sort(argument.arr, argument.low, argument.high-1);
	free(args);
	pthread_exit(0);
}

void * workerTwo(void * arg) {
	
	ArgsM args = *((ArgsM *) arg);	
	int * left = args.array + args.leftStart;
	int * right = args.array + args.rightStart;
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
		args.array[s++] = temp[i];
	}
	free(arg);
	free(temp);
	pthread_exit(0);
}

Args * createArgument(int * arr, int index) {
	Args * args = malloc(sizeof(* args));
	args->low = SET * (index+1) - SET;
	args->high = SET * (index+1);
	args->arr = arr;
	return args;
}

ArgsM * createArgumentM(int i, int multiplier) {
	ArgsM * args = malloc(sizeof(* args));
	args->leftStart = SET * i;
	args->rightStart = SET * (i+1); 
	args->setSize = SET;
	return args;
}

void sortPartitions(int * arr, int nrOfPartitions) {
	int i;
	for(i = 0; i < nrOfPartitions; i++) {
		Args * args = createArgument(arr, i);
		pthread_create(&threads[i], NULL, worker, args);
	}
	for(i = 0; i < nrOfPartitions; i++) {
		pthread_join(threads[i], NULL);
	}
}

void mergePartitions(int * arr, int nrOfPartitions, int multiplier) {
	int i, low = 0, high = MAX_ITEMS/nrOfPartitions;
	for(i = 0; i < nrOfPartitions; i++) {
		ArgsM * args = createArgumentM(i, multiplier);
		pthread_create(&threads[i], NULL, workerTwo, args);
	}
	for(i = 0; i < nrOfPartitions; i++) {
		pthread_join(threads[i], NULL);
	}
}

int main(int argc, char **argv) {
	srand((unsigned) time(NULL));
    init();
    removeOrderFile();
    sortPartitions(array, THREADS/1);
    mergePartitions(array, THREADS/2, 2);
    logOrder(array, MAX_ITEMS);
}*/
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
//#define MAX_ITEMS 16
#define MAX_THREADS 4
#define SET_SIZE (MAX_ITEMS/MAX_THREADS)
#define swap(v, a, b) {unsigned tmp; tmp=v[a]; v[a]=v[b]; v[b]=tmp;}

static int *v;

pthread_t tid[MAX_THREADS];
typedef struct {
	int end;
	int start;	
} Args;

typedef struct {
	unsigned leftStart;
	unsigned rightStart;
	unsigned setSize;
} MergeArgs;


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
		v[i] = rand() % 10;
	}	
}

static unsigned partition(int *v, unsigned low, unsigned high, unsigned pivot_index) {
    if (pivot_index != low)
        swap(v, low, pivot_index);

    pivot_index = low;
    low++;

    while (low <= high) {
        if (v[low] <= v[pivot_index])
            low++;
        else if (v[high] > v[pivot_index])
            high--;
        else
            swap(v, low, high);
    }

    if (high != pivot_index)
        swap(v, pivot_index, high);
    return high;
}

static void quick_sort(int *v, unsigned low, unsigned high) {
    unsigned pivot_index;
    
    if (low >= high)
        return;

    pivot_index = (low+high)/2;

    pivot_index = partition(v, low, high, pivot_index);

    if (low < pivot_index)
        quick_sort(v, low, pivot_index-1);
    if (pivot_index < high)
        quick_sort(v, pivot_index+1, high);
}

void * workerOne(void * arg) {
	
	Args args = *((Args *) arg);
	quick_sort(v, args.start, args.end-1);	
	free(arg);
	pthread_exit(0);
	
}

void * workerTwo(void * arg) {
	
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

void sort() {
	int i = 0;
	for(; i < MAX_THREADS; i++) {
		Args * args = malloc(sizeof(* args));
		args->start = SET_SIZE * (i+1) - SET_SIZE;
		args->end = SET_SIZE * (i+1);
		pthread_create(&tid[i], 0, workerOne, args);
	}
	i = 0;
	for(; i < MAX_THREADS; i++) {
		pthread_join(tid[i], NULL);
	}
}

void mergePartitions(int divider, int incre, int set) {

	int i = 0, counter = 0;
	for(; i < MAX_THREADS/divider; i++) {
		MergeArgs * args = malloc(sizeof(* args));
		args->leftStart = SET_SIZE * counter;
		counter += incre;
		args->rightStart = SET_SIZE * counter;
		counter += incre;
		args->setSize = SET_SIZE * set;
		pthread_create(&tid[i], 0, workerTwo, args);
	}	
	
	i = 0;
	for(; i < MAX_THREADS/divider; i++) {
		pthread_join(tid[i], NULL);
	}
}

int main(int argc, char **argv) {
	srand((unsigned) time(NULL));
    init_array();
    //removeOrderFile();
	sort();
	mergePartitions(2, 1, 1);
	mergePartitions(4, 2, 2);
	//logOrder(v, MAX_ITEMS);
}
