#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 2048
#define MAX_THREADS 4

static double a[SIZE][SIZE];
static double b[SIZE][SIZE];
static double c[SIZE][SIZE];

typedef struct {
	int startX;
}Args;

pthread_t tid[MAX_THREADS];

void * worker(void * args);

static void init_matrix(void) {
    int i, j;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
	    	a[i][j] = rand() % 10;
	    	b[i][j] = rand() % 10;
        }
    }
}

static void matmul_par() {
    
	int i = 0;
	int xCounter = 0;
	int yCounter = 0;
	int threadCounter = 0;
	for(; i < MAX_THREADS; ++i) {
		Args * args = malloc(sizeof(* args));
		args->startX = xCounter;
		
		xCounter += SIZE/MAX_THREADS;
	
		
		pthread_create(&tid[threadCounter++], 0, worker, args);
	} 

	int j = 0;
	for(; j < MAX_THREADS; ++j) {
		pthread_join(tid[j], NULL);
	}
}

void* worker(void * args) {

	Args * arg = args;
	int i,j,k;
	int endX = arg->startX + SIZE/MAX_THREADS;
	
	for(i = arg->startX; i < endX; ++i) {
		for(j = 0; j < SIZE; ++j) {
			c[i][j] = 0.0;
			for(k = 0; k < SIZE; ++k) {
				c[i][j] = c[i][j] + a[i][k] * b[k][j];	
			}
		}
	}		
	free(arg);
	pthread_exit(0);
}

void print_matrix(void) {
    int i, j;

    printf("Matrix A\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf(" %7.2f", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Matrix B\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf(" %7.2f", b[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Matrix C\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf(" %7.2f", c[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char **argv) {
	/*CLOCK_REALTIME, CLOCK_PROCESS_CPUTIME_ID, CLOCK_THREAD_CPUTIME_ID */
	srand((unsigned) time(NULL));

	struct timespec initStart, initEnd;
	clock_gettime(CLOCK_REALTIME, &initStart);
    init_matrix();
    clock_gettime(CLOCK_REALTIME, &initEnd);
    printTimespec(initStart, initEnd, "initialize");


    struct timespec mulStart, mulEnd;
    clock_gettime(CLOCK_REALTIME, &mulStart);
    matmul_par();
    clock_gettime(CLOCK_REALTIME, &mulEnd);
    printTimespec(mulStart, mulEnd, "matrix multiply");

    if(SIZE <= 16) {
        print_matrix();
    }
}

