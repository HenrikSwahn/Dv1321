#ifndef MATRIX_H
#define MATRIX_H

#include <string>

using namespace std;

class Matrix {

private:
	int **matrix;
	int size;

	void setup();

public:
	Matrix();
	Matrix(int size);
	~Matrix();

	int getElement(int X, int Y);
	void insertElement(int X, int Y, int element);
	int getSize();
	string toString();
};

#endif