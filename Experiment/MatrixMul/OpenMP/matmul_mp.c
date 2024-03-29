#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SIZE 10000

static double a[SIZE][SIZE];
static double b[SIZE][SIZE];
static double c[SIZE][SIZE];

void init_matrix(void) {

    int i, j;

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++) {
	       a[i][j] = rand() % 10;
	       b[i][j] = rand() % 10;
        }
}

void matmul_seq() {

    int i, j, k;

    #pragma omp parallel shared(a,b,c) private(i,j,k) num_threads(8)
    {   
        #pragma omp for schedule (static)
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                c[i][j] = 0.0;
                for (k = 0; k < SIZE; k++)
                    c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
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

    printf("Matrix B\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf(" %7.2f", b[i][j]);
        }
        printf("\n");
    }

    printf("Matrix C\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf(" %7.2f", c[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    
    srand((unsigned) time(NULL));
    init_matrix();
    removeResultFile();

    int i = 0;
    for(;i < 10; ++i) {
        struct timespec mulStart, mulEnd;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &mulStart);
        matmul_seq();
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &mulEnd);
        printTimespec(mulStart, mulEnd, "matrix multiply");
        logResult(mulStart, mulEnd);
    }
    
    if(SIZE <= 16) {
        print_matrix();
    }
}
