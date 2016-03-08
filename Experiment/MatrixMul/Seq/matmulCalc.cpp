#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

#define SIZE 1000

using namespace std;

void init(Matrix*);
Matrix* matmul(Matrix*, Matrix*);

int main() {
	srand(time(NULL));

	Matrix* matrix_a = new Matrix(SIZE);
	Matrix* matrix_b = new Matrix(SIZE);
	
	clock_t initTime = clock(), initDiff;
	init(matrix_a);
	init(matrix_b);
	initDiff = clock() - initTime;

	int initTimeMsec = initDiff * 1000 / CLOCKS_PER_SEC;
	cout << "Took: " << initTimeMsec << " msec to init matrix_a and matri_b" << endl;

	clock_t matTime = clock(), matDiff;
	Matrix* matrix_c = matmul(matrix_a, matrix_b);
	matDiff = clock() - matTime;

	int matTimeMsec = matDiff * 1000 / CLOCKS_PER_SEC;
	cout << "Took: " << matTimeMsec << " msec to matmul matrix_a and matrix_b" << endl;
	// cout << matrix_a->toString() << endl;
	// cout << matrix_b->toString() << endl;
	// cout << matrix_c->toString() << endl;

	delete(matrix_a);
	delete(matrix_b);
	delete(matrix_c);
	return 0;
}

void init(Matrix* matrix) {

	for(int i = 0, sizeX = matrix->getSize(); i < sizeX; ++i) {
		for(int j = 0, sizeY = matrix->getSize(); j < sizeY; ++j) {
			matrix->insertElement(i,j,rand() % 10);
		}
	}
}

Matrix* matmul(Matrix* a, Matrix* b) {
	Matrix* c = new Matrix(2);

	for(int i = 0, sizeX = a->getSize(); i < sizeX; ++i) {
		for(int j = 0, sizeY = b->getSize(); j < sizeY; j++) {
			int val = 0;
			for(int k = 0, sizeK = b->getSize(); k < sizeK; ++k) {
				val += a->getElement(i,k) * b->getElement(k,j);
				c->insertElement(i,j,val);
			}
		}
	}

	return c;
}

