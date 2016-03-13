#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "matrix.h"

#define SIZE 2
#define T_MAX 2

pthread_t tid[T_MAX];

using namespace std;

typedef struct {
	Matrix* matrix_a;
	Matrix* matrix_b;
	Matrix* matrix_c;
} MatrixContainer;

typedef struct {
	MatrixContainer* container;
	int X_begin;
	int Y_begin;
	int X_end;
	int Y_end;
}ThreadParam;

void init(Matrix*);
void* matmul(void *);

int main() {
	srand(time(NULL));
		
	MatrixContainer* container = new MatrixContainer;
	container->matrix_a = new Matrix(SIZE);
	container->matrix_b = new Matrix(SIZE);
	container->matrix_c = new Matrix(SIZE);

	clock_t initTime = clock(), initDiff;
	init(container->matrix_a);
	init(container->matrix_b);
	initDiff = clock() - initTime;

	int initTimeMsec = initDiff * 1000 / CLOCKS_PER_SEC;
	cout << "Took: " << initTimeMsec << " msec to init matrix_a and matri_b" << endl;

	clock_t matTime = clock(), matDiff;

	int x = 0;
	int y = 0;

	for(int i = 0; i < T_MAX; ++i) {
		
		ThreadParam* param = new ThreadParam;
		param->container = container;
		param->X_begin = x;
		param->X_end = x + (SIZE/T_MAX);

		pthread_create(&tid[i], NULL, matmul, (void*)param);

		x += SIZE / T_MAX;
	}

	for(int i = 0; i < T_MAX; ++i) {
		pthread_join(tid[i], NULL);
	}
	
	matDiff = clock() - matTime;

	int matTimeMsec = matDiff * 1000 / CLOCKS_PER_SEC;
	cout << "Took: " << matTimeMsec << " msec to matmul matrix_a and matrix_b" << endl;
	
	cout << container->matrix_a->toString() << endl;
	cout << container->matrix_b->toString() << endl;
	cout << container->matrix_c->toString() << endl;

	delete(container->matrix_a);
	delete(container->matrix_b);
	delete(container->matrix_c);
	delete(container);
	return 0;
}

void init(Matrix* matrix) {

	for(int i = 0, sizeX = matrix->getSize(); i < sizeX; ++i) {
		for(int j = 0, sizeY = matrix->getSize(); j < sizeY; ++j) {
			matrix->insertElement(i,j,rand() % 10);
		}
	}
}

void* matmul(void* threadParam) {
	ThreadParam* param = (ThreadParam*)threadParam;
	int size = param->container->matrix_a->getSize();
	
	for(int i = param->X_begin; i < param->X_end + SIZE/T_MAX; ++i) {
		for(int j = 0; j < SIZE; j++) {
			int val = 0;
			for(int k = param->X_begin; k < param->X_end + SIZE/T_MAX; ++k) {
				val += param->container->matrix_a->getElement(i,k) * param->container->matrix_b->getElement(k,j);
				param->container->matrix_c->insertElement(i,j,val);
			}
		}
	}

	delete(param);
}

