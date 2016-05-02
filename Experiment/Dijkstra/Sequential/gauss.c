#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
 
#define mat_elem(a, y, x, n) (a + ((y) * (n) + (x))) 
#define SOL_SIZE 3000
#define SYS_SIZE SOL_SIZE * SOL_SIZE
#define MIN -500
#define MAX 500

static double * sys;
static double * solution;
static double * x;

double fRand() {
	double f = (double)rand() / RAND_MAX;
	return MIN + f * (MAX - MIN);
}

void init () {
	sys = malloc(sizeof(double) * SYS_SIZE);
	solution = malloc(sizeof(double) * SOL_SIZE);
	x = malloc(sizeof(double) * SOL_SIZE);

	int i = 0;
	for(; i < SYS_SIZE; i++) {
		sys[i] = fRand();
	}
	i = 0;
	for(; i < SOL_SIZE; i++) {
		solution[i] = fRand();
	}
}

void printX() {
	int i = 0;
	for(; i < SOL_SIZE; i++) {
		printf("%g\n", x[i]);
	}
}

void printSol() {
	int i = 0;
	for(; i < SOL_SIZE; i++) {
		printf("%g, ", solution[i]);
	}
	printf("\n");
}

void printMat() {
	int i = 0, c = 0;
	for(; i < SYS_SIZE; i++) {
		printf("%g", sys[i]);
		c++;
		if(c == SOL_SIZE) {
			c = 0;
			printf("\n");
		}
		else {
			printf(", ");
		}
	}
}
 
void swap_row(double *a, double *b, int r1, int r2, int n) {
	double tmp, *p1, *p2;
	int i;
 
	if (r1 == r2) return;
	for (i = 0; i < n; i++) {
		p1 = mat_elem(a, r1, i, n);
		p2 = mat_elem(a, r2, i, n);
		tmp = *p1, *p1 = *p2, *p2 = tmp;
	}
	tmp = b[r1], b[r1] = b[r2], b[r2] = tmp;
}
 
void gauss_eliminate(double *a, double *b, double *x, int n) {
#define A(y, x) (*mat_elem(a, y, x, n))
	int i, j, col, row, max_row,dia;
	double max, tmp;
 
	for (dia = 0; dia < n; dia++) {
		max_row = dia, max = A(dia, dia);
 
		for (row = dia + 1; row < n; row++)
			if ((tmp = fabs(A(row, dia))) > max)
				max_row = row, max = tmp;
 
		swap_row(a, b, dia, max_row, n);
 
		for (row = dia + 1; row < n; row++) {
			tmp = A(row, dia) / A(dia, dia);
			for (col = dia+1; col < n; col++)
				A(row, col) -= tmp * A(dia, col);
			A(row, dia) = 0;
			b[row] -= tmp * b[dia];
		}
	}
	for (row = n - 1; row >= 0; row--) {
		tmp = b[row];
		for (j = n - 1; j > row; j--)
			tmp -= x[j] * A(row, j);
		x[row] = tmp / A(row, row);
	}
#undef A
}
 
int main(void) {
	srand((unsigned) time(NULL));
	init();

	if(SOL_SIZE < 36) {
		printMat();
		printSol();
	}

	gauss_eliminate(sys, solution, x, SOL_SIZE);

	if(SOL_SIZE < 36) {
		printX();
	}

 	free(sys);
 	free(solution);
 	free(x);
	return 0;
}