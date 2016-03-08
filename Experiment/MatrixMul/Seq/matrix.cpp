#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

#include "matrix.h"

Matrix::Matrix() {
	size = 10;
	matrix = new int*[size];
	setup();
}

Matrix::Matrix(int size) {
	this->size = size;
	matrix = new int*[this->size];
	setup();
}

Matrix::~Matrix() {

	cout << "De-constructing matrix...." << endl;

	for(int i = 0; i < size; ++i) {
		delete(matrix[i]);
	}

	delete(matrix);
}

void Matrix::setup() {

	srand(time(NULL));

	for(int i = 0; i < size; ++i) {
		matrix[i] = new int[size];
	}
}

int Matrix::getElement(int X, int Y) {

	if(X >= 0 && X < size) {
		if(Y >= 0 && Y < size) {
			return matrix[X][Y];
		}
	}

	return -1;
}

void Matrix::insertElement(int X, int Y, int element) {
	if(X >= 0 && X < size) {
		if(Y >= 0 && Y < size) {
			matrix[X][Y] = element;
		}
	}	
}

int Matrix::getSize() {
	return size;
}

string Matrix::toString() {
	ostringstream output;

	for(int i = 0; i < size; ++i) {
		for(int j = 0; j < size; ++j) {
			output << matrix[i][j] << endl;
		}
	}

	return output.str();
}